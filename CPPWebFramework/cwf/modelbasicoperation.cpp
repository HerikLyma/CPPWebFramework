#include "modelbasicoperation.h"

CWF_BEGIN_NAMESPACE

ModelBasicOperation::ModelBasicOperation(SqlDatabaseStorage &connection) : connection(connection)
{
}

bool ModelBasicOperation::createTable(const QString &name)
{
    SqlQueryManager queryManager(connection);
    QJsonObject json = queryManager.exec(queryManager.createTable(name));
    bool success = json["success"].toBool();
    if(!success)
    {
        qFatal("%s", ("ModelBasicOperation::createTable: CREATE TABLE " + name + json["message"].toString()).toStdString().data());
    }

    queryManager.reset();

    queryManager.insert("table_version", "table_name, version_number");
    queryManager.prepare();
    queryManager.addBindValue(name);
    queryManager.addBindValue(0);
    json = queryManager.exec();
    success = json["success"].toBool();
    if(!success)
    {
        qFatal("%s", ("ModelBasicOperation::createTable: INSERT INTO table_version " + json["message"].toString()).toStdString().data());
    }

    return success;
}

bool ModelBasicOperation::createVersionTable()
{
    const auto &json = SqlQueryManager(connection).exec("CREATE TABLE table_version (table_name TEXT, version_number INTEGER);");
    bool success = json["success"].toBool();
    if(!success)
    {
        qFatal("ModelBasicOperation::createTable: CREATE TABLE table_version (tableName TEXT, version_number INTEGER);");
    }
    return success;
}

bool ModelBasicOperation::addFieldToTable(const QString &fieldName,
                                     const QVariant::Type type,
                                     const QString &tableName
                                     ) const
{
    QString fieldTypeStr = convertQVariantTypeToSQLType(type);

    SqlQueryManager queryManager(connection);
    QJsonObject json = queryManager.exec(queryManager.alterTable(tableName).addColumn(fieldName, fieldTypeStr).getQueryText());
    bool success = json.value("success").toBool();
    if(!success)
    {
        qDebug() << "ModelBasicOperation::addFieldToTable:"
                 << "ALTER TABLE"
                 << json.value("message").toString();
    }

    return success;
}

bool ModelBasicOperation::changeTableVersion(const QString& tableName, qint32 version) const
{
    SqlQueryManager queryManager(connection);
    QJsonObject json;

    queryManager.update("table_version", "version_number=?")
                .where("table_name=?");
    queryManager.prepare();
    queryManager.addBindValue(version);
    queryManager.addBindValue(tableName);

    json = queryManager.exec();
    bool success = json["success"].toBool();
    if(!success)
    {
        qFatal("%s", ("ModelBasicOperation::changeTableVersion: Error in UPDATE version message:" +
                      json["message"].toString()).toStdString().data());
    }

    return success;
}


QStringList ModelBasicOperation::fields(const QString &tableName) const
{
    QStringList output;
    const auto &record = connection.getDatabase().record(tableName);
    for(int i = 0, numOfFields = record.count(); i < numOfFields; i++)
    {
        output.push_back(record.fieldName(i));
    }
    return output;
}

qint32 ModelBasicOperation::tableVersion(const QString &tableName) const
{
    SqlQueryManager queryManager(connection);
    QJsonObject json;
    QJsonArray jsonArray;

    queryManager.select("version_number", "table_version").where("table_name=?");
    queryManager.prepare();
    queryManager.addBindValue(tableName);
    json = queryManager.exec();

    if(!json.value("success").toBool() )
    {
        qFatal("%s", ("ModelBasicOperation::tableVersion: SELECT " + json["message"].toString()).toStdString().data());
    }
    auto array = queryManager.toJson();
    if(array.isEmpty())
    {
        qFatal("%s", ("ModelBasicOperation::tableVersion: Empty array " + json["message"].toString()).toStdString().data());
    }
    int version = array.at(0).toObject()["version_number"].toInt();
    return version;
}

QString ModelBasicOperation::convertQVariantTypeToSQLType(const QVariant::Type type) const
{
    QString output("");

    switch(type)
    {
        case QVariant::Invalid:
        {
            qDebug() << "ModelBasicOperation::convertQVariantTypeToSQLType:"
                     << "Type was invalid";
            qFatal("Type was invalid");
        }
        case QVariant::Type::ByteArray:
        {
            output = "BLOB";
            break;
        }
        case QVariant::Int:
        {
            output = "INTEGER";
            break;
        }
        case QVariant::Bool:
        {
            output = "INTEGER";
            break;
        }
        case QVariant::LongLong:
        {
            output = "INTEGER";
            break;
        }
        case QVariant::String:
        {
            output = "TEXT";
            break;
        }
        case QVariant::Double:
        {
            output = "REAL";
            break;
        }
        default:
        {
            qDebug() << "ModelBasicOperation::convertQVariantTypeToSQLType:"
                     << "Type was not defined";
            qFatal("Type was not defined");
        }
    }

    return output;
}

qint64 ModelBasicOperation::save(const QString &tableName, const QMap<QString, QVariant> &map)
{
    QVariant idValue = map["id"];
    qint64 id = idValue.toInt();

    if(id == -1)
    {
        id = insertEntry(tableName, map);
    }
    else
    {
        id = updateEntry(tableName, map);
    }

    return id;
}

QVector<QMap<QString, QVariant> > ModelBasicOperation::buildVector(const QString& tableName,
                                                const QMap<QString, QVariant> &selectCondition,
                                                const QStringList& props,
                                                const QString& orderBy
                                              )
{
    /* Example of insert query
        SELECT id, type, datetime, entry, comment, status, priority, observerId, observationId FROM data WHERE id = ?;
    */

    CWF::SqlQuery query(connection);
    QJsonObject json;

    // *****************************
    // Query contruction
    // *****************************

    QString what ("");

    // Loop on all the object properties
    for(int i=0, ie=props.size(); i<ie; i++)
    {
        what += props.at(i);

        if(i >= 0  && i < ie-1)
            what += ", ";
    }

    QString cond ("");

    QVector<QVariant> selectValues;
    qint32 count = 0;
    qint32 selectCondNum = selectCondition.size();

    // Loop on all the select conditions
    for(const auto& it : selectCondition.toStdMap())
    {
        const QString& name = it.first;
        const QVariant& value = it.second;

        cond += name + " = ?";

        if(count >= 0 && count < selectCondNum-1)
            cond += " AND ";

        selectValues.push_back(value);

        count++;
    }

    SqlQueryManager queryManager(connection);
    queryManager.select(what, tableName)
                .where(cond)
                .orderBy(orderBy);

    QString queryText = queryManager.textQuery(true);

    // Prepare the query
    query.prepare(queryText);

    // *****************************
    // Bindings with values
    // *****************************

    // Loop on all the prop inserted in the sql query
    for(const auto & v : selectValues)
    {
        query.addBindValue(v);
    }

    // *****************************
    // Run the query
    // *****************************

    json = query.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::build:"
                 << "Error in insert for table" << tableName
                 << json.value("message").toString() << query.executedQuery()
                 ;
    }

    // *****************************
    // Get the result
    // *****************************

    QVector<QMap<QString, QVariant> > output;

    if(query.first() )
    {
        do {
            QMap<QString, QVariant> map;

            for(const QString& propName : props)
            {
                QVariant val = query.value(propName);

                map.insert(propName, val);
            }

            output.push_back(map);
        }
        while(query.next() );
    }

    return output;
}

QMap<QString, QVariant> ModelBasicOperation::build(const QString& tableName,
                                              const QMap<QString, QVariant> &selectCondition,
                                              const QStringList& props)
{
    QVector<QMap<QString, QVariant> > output = buildVector(tableName, selectCondition, props);
    if(!output.empty())
        return output.at(0);
    return QMap<QString, QVariant>();
}

bool ModelBasicOperation::remove(const QString &tableName, const qint64 &id)
{
    CWF::SqlQuery query(connection);
    SqlQueryManager qm(connection);
    qm.remove(tableName, "id=?");

    QString textQuery = qm.textQuery(true);

    query.prepare(textQuery);
    query.bindValue(0, id);

    QJsonObject json;
    json = query.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::remove:"
                 << "Error in index creation for table" << tableName
                 << json.value("message").toString() << query.executedQuery();

        return false;
    }

    return true;
}

bool ModelBasicOperation::createIndex(const QString &tableName, const QString &column, bool unique) const
{
    QString indexName = QString("index_") + tableName + QString("_") + column;

    CWF::SqlQuery query(connection);
    QJsonObject json;
    SqlQueryManager queryManager(connection);
    queryManager.createIndex(indexName, tableName, column, unique);

    QString queryText = queryManager.textQuery(true);
    query.prepare(queryText);

    json = query.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::createIndex:"
                 << "Error in index creation for table" << tableName
                 << json.value("message").toString() << query.executedQuery();

        return false;
    }

    return true;
}

QString ModelBasicOperation::constructInsertTextQuery(const QString& tableName, const QMap<QString, QVariant> &map, QVector<QVariant>& values)
{
    QString fields;

    for(const auto &it : map.toStdMap() )
    {
        const QString  &name  = it.first.toLower();
        const QVariant &value = it.second;

        if(name == "id")
            continue;

        fields += name;
        fields += ",";

        values.push_back(value);
    }
    fields = fields.remove(fields.size() - 1, 1);

    SqlQueryManager queryManager(connection);
    queryManager.insert(tableName, fields);

    QString queryText = queryManager.textQuery(true);

    return queryText;
}

QString ModelBasicOperation::constructUpdateTextQuery(const QString &tableName, const QMap<QString, QVariant> &map, QVector<QVariant> &values)
{
    QString fieldValues;
    for(const auto& it : map.toStdMap() )
    {
        const QString&  name  = it.first;
        const QVariant& value = it.second;

        if(name == "id")
            continue;
        fieldValues += name + " = ?,";
        values.push_back(value);
    }
    fieldValues = fieldValues.remove(fieldValues.size() - 1, 1);
    SqlQueryManager queryManager(connection);
    queryManager.update(tableName, fieldValues);
    queryManager.where("id=?");

    return queryManager.getQueryText() + ";";
}

qint64 ModelBasicOperation::insertEntry(const QString &tableName, const QMap<QString, QVariant> &map)
{
    CWF::SqlQuery query(connection);
    QJsonObject json;
    QVector<QVariant> values;
    query.prepare(constructInsertTextQuery(tableName, map, values));

    for(const auto &it : values)
    {
        query.addBindValue(it);
    }

    json = query.exec();
    if(!json["success"].toBool())
    {
        qDebug() << "ModelBasicOperation::insertEntry:"
                 << "Error in insert for table" << tableName
                 << json["message"].toString() << query.executedQuery();
        return -1;
    }

    return query.lastInsertId().toInt();
}

qint64 ModelBasicOperation::updateEntry(const QString &tableName, const QMap<QString, QVariant> &map)
{
    CWF::SqlQuery query(connection);
    QVector<QVariant> values;
    query.prepare(constructUpdateTextQuery(tableName, map, values));
    for(const auto &it : values)
    {
        query.addBindValue(it);
    }
    int id = map.value("id").toInt();
    query.addBindValue(map.value("id"));
    QJsonObject json = query.exec();
    if(!json["success"].toBool())
    {
        id = -1;
        qDebug() << "ModelBasicOperation::updateEntry: Error in insert for table" << tableName << json["message"].toString();
    }
    return id;
}

CWF_END_NAMESPACE

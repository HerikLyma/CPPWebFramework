#include "modelbasicoperation.h"

CWF_BEGIN_NAMESPACE

bool ModelBasicOperation::createTable(const QString &name)
{
    bool success = true;

    SqlQueryManager queryManager;
    QJsonObject json;

    // Creation of the table
    queryManager.createTable(name);
    queryManager.prepare();
    json = queryManager.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::createTable" << "CREATE TABLE" << name << json.value("message").toString();
        success = false;
    }

    queryManager.reset();

    queryManager.insert(name, "tableName, number");
    queryManager.addBindValue(name);
    queryManager.addBindValue(0);
    json = queryManager.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::createTable" << "INSERT INTO version" << name << json.value("message").toString();
        success = false;
    }

    return success;
}

bool ModelBasicOperation::addFieldToTable(const QString &fieldName,
                                     const QVariant::Type type,
                                     const QString &tableName
                                     ) const
{
    bool success = true;

    QString fieldTypeStr = convertQVariantTypeToSQLType(type);

    SqlQueryManager queryManager;
    QJsonObject json;

    queryManager.alterTable(tableName)
                .addColumn(fieldName, fieldTypeStr)
            ;
    queryManager.prepare();
    json = queryManager.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::addFieldToTable:"
                 << "ALTER TABLE"
                 << json.value("message").toString()
                 ;

        success = false;
    }

    return success;
}

bool ModelBasicOperation::changeTableVersion(const QString& tableName, qint32 version) const
{
    bool success = true;

    SqlQueryManager queryManager;
    QJsonObject json;

    queryManager.update("version", "number=?")
                .where("tableName=?");
    queryManager.prepare();
    queryManager.addBindValue(version);
    queryManager.addBindValue(tableName);

    json = queryManager.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::changeTableVersion:"
                 << "Error in UPDATE version"
                 << "message:"<<json.value("message").toString();

        success = false;
    }

    return success;
}

QStringList ModelBasicOperation::tables() const
{
    QStringList output;

    QSqlDatabase& db = DbStorage::_storage.getDatabase();
    output = db.tables();

    return output;
}

QStringList ModelBasicOperation::fields(const QString &tableName) const
{
    QStringList output;
    QSqlDatabase& db = DbStorage::_storage.getDatabase();
    QSqlRecord record = db.record(tableName);

    int numOfFields = record.count();

    for(int i=0; i<numOfFields; i++)
    {
        const auto &field = record.fieldName(i);
        output.push_back(field);
    }
    return output;
}

qint32 ModelBasicOperation::tableVersion(const QString &tableName) const
{
    SqlQueryManager queryManager;
    QJsonObject json;
    QJsonArray jsonArray;

    queryManager.select("id, number", "version").where("tableName=?");
    queryManager.prepare();
    queryManager.addBindValue(tableName);

    json = queryManager.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::tableVersion:"
                 << "SELECT"
                 << json.value("message").toString();
    }

    jsonArray = queryManager.toJson();

    if(jsonArray.isEmpty() )
    {
        qDebug() << "ModelBasicOperation::tableVersion:"
                 << "Empty array"
                 << json.value("message").toString();
    }

    qint32 versionNumber = jsonArray.at(1).toInt();

    return versionNumber;
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
    // Look for the id property
    QVariant idValue = map["id"];
    qint64 id = idValue.toInt();

    // Case where the object is a new one
    if(id==-1)
    {
        id = insertEntry(tableName, map);
    }
    // Case where the object already exists
    else
    {
        updateEntry(tableName, map);
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

    CWF::SqlQuery query(DbStorage::_storage);
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

    SqlQueryManager queryManager;
    queryManager.select(what, tableName)
                .where(cond)
                .orderBy(orderBy)
            ;

    QString queryText = queryManager.textQuery(true);

    // Prepare the query
    query.prepare(queryText);

    // *****************************
    // Bindings with values
    // *****************************

    // Loop on all the prop inserted in the sql query
    for(int i=0, ie=selectValues.size(); i<ie; i++)
    {
        const QVariant& v = selectValues.at(i);
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

    if(output.size() > 0 )
        return output.at(0);
    else
        return QMap<QString, QVariant>();
}

bool ModelBasicOperation::remove(const QString &tableName, const qint64 &id)
{
    CWF::SqlQuery query(DbStorage::_storage);

    // *****************************
    // Query contruction
    // *****************************

    SqlQueryManager qm;
    qm.remove(tableName, "id=?");

    QString textQuery = qm.textQuery(true);

    query.prepare(textQuery);

    // *****************************
    // Bindings with values
    // *****************************

    query.bindValue(0, id);

    // *****************************

    // *****************************
    // Run the query
    // *****************************

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

    /* Example of insert query
        CREATE [UNIQUE] INDEX index_name ON table_name(indexed_column);
    */

    CWF::SqlQuery query(DbStorage::_storage);
    QJsonObject json;

    // *****************************
    // Query contruction
    // *****************************

    SqlQueryManager queryManager;
    queryManager.createIndex(indexName, tableName, column, unique);

    QString queryText = queryManager.textQuery(true);

    // Prepare the query
    query.prepare(queryText);

    // *****************************
    // Run the query
    // *****************************

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

bool ModelBasicOperation::isTableInDb(const QString &tableName) const
{
    QSqlDatabase& db = DbStorage::_storage.getDatabase();

    bool exist = db.tables().contains( QLatin1String(tableName.toLatin1() ) );

    return exist;
}

QString ModelBasicOperation::constructInsertTextQuery(const QString& tableName, const QMap<QString, QVariant> &map, QVector<QVariant>& values)
{
    QString fields ("");

    qint32 count = 0;
    qint32 numOfProps = map.size();

    // Loop on all the properties
    for(const auto& it : map.toStdMap() )
    {
        const QString& name = it.first;
        const QVariant& value = it.second;

        // Skip the id field since it is auto set
        if(name == "id")
            continue;

        fields += name;

        if(count >= 0 && count < numOfProps-2)
            fields += ", ";

        values.push_back(value);

        count++;
    }

    SqlQueryManager queryManager;
    queryManager.insert(tableName, fields);

    QString queryText = queryManager.textQuery(true);

    return queryText;
}

QString ModelBasicOperation::constructUpdateTextQuery(const QString &tableName, const QMap<QString, QVariant> &map, QVector<QVariant> &values)
{
    QString fieldValues ("");

    qint32 count = 0;
    qint32 numOfProps = map.size();

    // Loop on all the properties
    for(const auto& it : map.toStdMap() )
    {
        const QString& name = it.first;
        const QVariant& value = it.second;

        // Skip the id field since it is auto set
        if(name == "id")
            continue;

        fieldValues += name + " = ?";

        if(count >= 0 && count < numOfProps-2)
            fieldValues += ", ";

        values.push_back(value);

        count++;
    }

    SqlQueryManager queryManager;
    queryManager.update(tableName, fieldValues);
    queryManager.where("id=?");

    QString queryText = queryManager.textQuery(true);

    return fieldValues;
}

qint64 ModelBasicOperation::insertEntry(const QString &tableName, const QMap<QString, QVariant> &map)
{
    /* Example of insert query
        INSERT INTO tableName(priority, entryOrder) VALUES(?,?));
    */

    CWF::SqlQuery query(DbStorage::_storage);
    QJsonObject json;

    // *****************************
    // Query contruction
    // *****************************

    QVector<QVariant> values;
    QString queryText = constructInsertTextQuery(tableName, map, values);

    // Prepare the query
    query.prepare(queryText);

    // *****************************
    // Bindings with values
    // *****************************

    // Loop on all the prop inserted in the sql query
    for(int i=0, ie=values.size(); i<ie; i++)
    {
        const QVariant& v = values.at(i);
        query.addBindValue(v);
    }

    // *****************************
    // Run the query
    // *****************************

    json = query.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::insertEntry:"
                 << "Error in insert for table" << tableName
                 << json.value("message").toString() << query.executedQuery();
    }

    return query.lastInsertId().toInt();
}

void ModelBasicOperation::updateEntry(const QString &tableName, const QMap<QString, QVariant> &map)
{
    /* Example of update query
        UPDATE data SET datetime = ?, type = ? WHERE id = ?
    */

    CWF::SqlQuery query(DbStorage::_storage);
    QJsonObject json;

    // *****************************
    // Query contruction
    // *****************************

    QVector<QVariant> values;
    QString queryText = constructUpdateTextQuery(tableName, map, values);

    // Prepare the query
    query.prepare(queryText);

    // *****************************
    // Bindings with values
    // *****************************

    // Loop on all the prop inserted in the sql query
    // Loop on all the properties
    for(int i=0; i<values.size(); i++)
    {
        const QVariant& v = values.at(i);
        query.addBindValue(v);
    }

    query.addBindValue(map.value("id") );

    // *****************************
    // Run the query
    // *****************************

    json = query.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "ModelBasicOperation::updateEntry:"
                 << "Error in insert for table" << tableName
                 << json.value("message").toString();
    }
}

CWF_END_NAMESPACE

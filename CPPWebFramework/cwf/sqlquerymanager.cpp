#include "sqlquerymanager.h"
#include "model.h"
#include "qsqldriver.h"
#include "metaclassparser.h"
#include <QDebug>

CWF_BEGIN_NAMESPACE

inline void addSpace(QString &value)
{
    if(!value.isEmpty() && !value.endsWith(" "))
        value += " ";
}

inline void executeQry(const QJsonObject &json, const QString &queryText)
{
    if(!json["success"].toBool() )
    {
        qDebug() << "SqlQueryManager::exec:"
                 << "Error: " << json["message"].toString()
                 << " query: " << queryText;
    }
}

void SqlQueryManager::reset()
{
    queryText = "";
    query.clear();
    bindingDone = 0;
}

QString SqlQueryManager::createTable(const QString &tableName)
{
    const auto &type = connection.getType();
    if(type == "QSQLITE")
    {
        queryText = "CREATE TABLE " + tableName + " (id INTEGER PRIMARY KEY AUTOINCREMENT);";
    }
    else if(type == "QPSQL")
    {
        queryText = "CREATE TABLE " + tableName + " (id serial PRIMARY KEY);";
    }
    else
    {
        qFatal("%s", (type + " is not supported yet!").toStdString().data());
    }
    return queryText;
}

void SqlQueryManager::createIndex(const QString &indexName, const QString &tableName, const QString &field, bool unique)
{
    queryText = "CREATE ";

    if(unique)
        queryText += "UNIQUE ";

    queryText += "INDEX ";
    queryText += indexName + " ON " + tableName + " ( " + field + " );";
}

SqlQueryManager &SqlQueryManager::alterTable(const QString &tableName)
{
    addSpace(queryText);
    queryText += "ALTER TABLE " + tableName;
    return *this;
}

SqlQueryManager &SqlQueryManager::addColumn(const QString &field, const QString &type)
{
    addSpace(queryText);
    queryText += "ADD COLUMN " + field + " " + type;
    return *this;
}

SqlQueryManager& SqlQueryManager::select(const QString &what, const QString &tableName)
{
    addSpace(queryText);
    queryText += "SELECT " + what + " FROM " + tableName;
    return *this;
}

SqlQueryManager &SqlQueryManager::count(const QString &what, const QString &tableName)
{
    addSpace(queryText);
    queryText += "COUNT " + what + " FROM " + tableName;
    return *this;
}

SqlQueryManager &SqlQueryManager::insert(const QString &tableName, const QString &fields)
{
    addSpace(queryText);
    queryText += "INSERT INTO " + tableName + " (" + fields + ") ";
    queryText += "VALUES(";

    for(int i = 0, fNum = fields.count(","); i < fNum; ++i)
    {
        queryText += "?,";
    }
    queryText += "?);";

    return *this;
}

SqlQueryManager &SqlQueryManager::remove(const QString &tableName, const QString &cond)
{
    addSpace(queryText);
    queryText += "DELETE FROM " + tableName + " WHERE " + cond;
    return *this;
}

SqlQueryManager &SqlQueryManager::update(const QString &tableName, const QString &fieldValue)
{
    addSpace(queryText);
    queryText += "UPDATE " + tableName + " SET " + fieldValue;
    return *this;
}

SqlQueryManager &SqlQueryManager::where(const QString &c)
{
    addSpace(queryText);
    queryText += " WHERE " + c;
    return *this;
}

SqlQueryManager &SqlQueryManager::orderBy(const QString &c)
{
    addSpace(queryText);
    queryText += "ORDER BY " + c;
    return *this;
}

SqlQueryManager &SqlQueryManager::leftJoin(const QString& tableName, const QString& cond)
{
    addSpace(queryText);
    queryText += "LEFT JOIN " + tableName + " ON " + cond;
    return *this;
}

SqlQueryManager &SqlQueryManager::innerJoin(const QString &tableName, const QString &cond)
{
    addSpace(queryText);
    queryText += "INNER JOIN " + tableName + " ON " + cond;
    return *this;
}


SqlQueryManager &SqlQueryManager::addBindValue(const QVariant& v)
{
    query.bindValue(bindingDone, v);
    ++bindingDone;
    return *this;
}

bool SqlQueryManager::prepare()
{
    if(!queryText.endsWith(";"))
        queryText += ";";

    if(!query.prepare(queryText))
    {
        qDebug() << "****** SqlQueryManager::prepare *******";
        qDebug() << "Error with: " << queryText;
        qDebug() << "************************************";

        return false;
    }
    return true;
}

QJsonObject SqlQueryManager::exec()
{
    const auto &json = query.exec();
    executeQry(json, queryText);
    return json;
}

QJsonObject SqlQueryManager::exec(const QString &sql)
{
    const auto &json = query.exec(sql);
    executeQry(json, queryText);
    return json;
}

QString SqlQueryManager::textQuery(bool addEndDot) const
{
    QString query = queryText;

    if(addEndDot)
    {
        if(!query.endsWith(";"))
            query += ";";
    }

    return query;
}

QString SqlQueryManager::prefixPropNames(Model &model)
{
    const auto &propNames = MetaClassParser(&model, true).getAllPropertiesNames();
    QString tableName = model.getTableName(), text;

    for(const auto &propName : propNames)
    {
        if(text != "")
            text += ", ";

        text += propName;
        text += " AS ";
        text += tableName;
        text += "_";
        text += propName;
    }

    return text;
}

CWF_END_NAMESPACE

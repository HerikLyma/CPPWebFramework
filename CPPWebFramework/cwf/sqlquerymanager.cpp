#include "sqlquerymanager.h"
#include "model.h"
#include "qsqldriver.h"
#include "metaclassparser.h"
#include <QDebug>

CWF_BEGIN_NAMESPACE

void SqlQueryManager::reset()
{
    m_queryText = "";
    m_query.clear();
    m_bindingDone = 0;
}

QString SqlQueryManager::createTable(const QString &tableName)
{
    const auto &type = connection.getType();
    if(type == "QSQLITE")
    {
        m_queryText = "CREATE TABLE " + tableName + " (id INTEGER PRIMARY KEY AUTOINCREMENT);";
    }
    else if(type == "QPSQL")
    {
        m_queryText = "CREATE TABLE " + tableName + " (id serial PRIMARY KEY);";
    }
    else
    {
        qFatal("%s", (type + " is not supported yet!").toStdString().data());
    }
    return m_queryText;
}

void SqlQueryManager::createIndex(const QString &indexName, const QString &tableName, const QString &field, bool unique)
{
    m_queryText = "CREATE ";

    if(unique) m_queryText += "UNIQUE ";

    m_queryText += "INDEX ";
    m_queryText += indexName + " ON " + tableName + " ( " + field + " );";
}

SqlQueryManager &SqlQueryManager::alterTable(const QString &tableName)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "ALTER TABLE " + tableName;

    return *this;
}

SqlQueryManager &SqlQueryManager::addColumn(const QString &field, const QString &type)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "ADD COLUMN "+field+" "+type;

    return *this;
}

SqlQueryManager& SqlQueryManager::select(const QString &what, const QString &tableName)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "SELECT " + what + " FROM " + tableName;

    return *this;
}

SqlQueryManager &SqlQueryManager::count(const QString &what, const QString &tableName)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "COUNT " + what + " FROM " + tableName;

    return *this;
}

SqlQueryManager &SqlQueryManager::insert(const QString &tableName, const QString &fields)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "INSERT INTO " + tableName + " (" + fields + ") ";
    m_queryText += "VALUES(";

    for(int i = 0, fNum = fields.count(","); i < fNum; ++i)
    {
        m_queryText += "?,";
    }
    m_queryText += "?);";

    return *this;
}

SqlQueryManager &SqlQueryManager::remove(const QString &tableName, const QString &cond)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "DELETE FROM " + tableName + " WHERE " + cond;

    return *this;
}

SqlQueryManager &SqlQueryManager::update(const QString &tableName, const QString &fieldValue)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "UPDATE " + tableName + " SET " + fieldValue;

    return *this;
}

SqlQueryManager &SqlQueryManager::where(const QString &c)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += " WHERE " + c;

    return *this;
}

SqlQueryManager &SqlQueryManager::orderBy(const QString &c)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "ORDER BY " + c;

    return *this;
}

SqlQueryManager &SqlQueryManager::leftJoin(const QString& tableName, const QString& cond)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "LEFT JOIN " + tableName + " ON " + cond;

    return *this;
}

SqlQueryManager &SqlQueryManager::innerJoin(const QString &tableName, const QString &cond)
{
    if(!m_queryText.isEmpty() && !m_queryText.endsWith(" "))
        m_queryText += " ";

    m_queryText += "INNER JOIN " + tableName + " ON " + cond;

    return *this;
}


SqlQueryManager &SqlQueryManager::addBindValue(const QVariant& v)
{
    m_query.bindValue(m_bindingDone, v);

    // Increment of 1 the binding counter
    ++m_bindingDone;

    return *this;
}

bool SqlQueryManager::prepare()
{
    if(!m_queryText.endsWith(";"))
        m_queryText += ";";

    if(!m_query.prepare(m_queryText))
    {
        qDebug() << "****** SqlQueryManager::prepare *******";
        qDebug() << "Error with: " << m_queryText;
        qDebug() << "************************************";

        return false;
    }
    return true;
}

QJsonObject SqlQueryManager::exec()
{
    QJsonObject json = m_query.exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "SqlQueryManager::exec:"
                 << "Error: " << json.value("message").toString()
                 << " query: " << m_queryText;
    }

    return json;
}

QJsonObject SqlQueryManager::exec(const QString &sql)
{
    QJsonObject json = m_query.exec(sql);

    if(!json.value("success").toBool() )
    {
        qDebug() << "SqlQueryManager::exec:"
                 << "Error: " << json.value("message").toString()
                 << " query: " << m_queryText;
    }

    return json;
}

QJsonArray SqlQueryManager::toJson()
{
    return m_query.toJson();
}

QString SqlQueryManager::textQuery(bool addEndDot) const
{
    QString query = m_queryText;

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

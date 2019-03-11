#include "sqlquerymanager.h"
#include "model.h"

CWF_BEGIN_NAMESPACE

SqlQueryManager::SqlQueryManager()
{
    m_query = std::make_shared<CWF::SqlQuery>(DbStorage::_storage);
    m_queryText = "";
    m_bindingDone = 0;
}

void SqlQueryManager::reset()
{
    m_queryText = "";
    m_query->clear();
    m_bindingDone = 0;
}

void SqlQueryManager::createTable(const QString &tableName)
{
    m_queryText = "CREATE TABLE " + tableName + " ("
                //"id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY"
                + "id INTEGER PRIMARY KEY AUTOINCREMENT"
                + ");"
            ;
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

    m_queryText += "ALTER TABLE "+tableName;

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

    m_queryText += "INSERT INTO "+tableName+" ("+fields+") ";

    m_queryText += "VALUES(";

    // Count the number of given fields
    int fNum = fields.count(",")+1;
    // Loop on all fields
    for(int i=0; i<fNum; ++i)
    {
        m_queryText += "?";

        if(i >= 0 && i < fNum-1)
            m_queryText += ",";
    }

    m_queryText += ");";

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

    m_queryText += "WHERE " + c;

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
    m_query->bindValue(m_bindingDone, v);

    // Increment of 1 the binding counter
    ++m_bindingDone;

    return *this;
}

bool SqlQueryManager::prepare()
{
    // Add a ";" if not present at the end of the query
    if(!m_queryText.endsWith(";") )
        m_queryText += ";";

    bool success = m_query->prepare(m_queryText);

    if(!success)
    {
        qDebug() << "****** SqlQueryManager::prepare *******";
        qDebug() << "Error with: "<<m_queryText;
        qDebug() << "************************************";

        return false;
    }

    return true;
}

QJsonObject SqlQueryManager::exec()
{
    QJsonObject json = m_query->exec();

    if(!json.value("success").toBool() )
    {
        qDebug() << "SqlQueryManager::exec:"
                 << "Error: " << json.value("message").toString()
                 << " query: " << m_queryText
                 ;
    }

    return json;
}

QJsonArray SqlQueryManager::toJson()
{
    return m_query->toJson();
}

QString SqlQueryManager::textQuery(bool addEndDot) const
{
    QString query = m_queryText;

    if(addEndDot)
    {
        // Add a ";" if not present at the end of the query
        if(!query.endsWith(";") )
            query += ";";
    }

    return query;
}

QString SqlQueryManager::prefixPropNames(const Model &model) const
{
    QStringList propNames = model.listAllProperties();
    QString tableName = model.getTableName();

    QString text ("");

    for(const QString& propName : propNames)
    {
        if(text != "")
            text += ", ";

        text += propName+" AS "+tableName+"_"+propName;
    }

    return text;
}

CWF_END_NAMESPACE

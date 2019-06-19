#ifndef SQLQUERYMANAGER_HH
#define SQLQUERYMANAGER_HH

#include "sqlquery.h"
#include "cppwebframework_global.h"

#include <memory>

CWF_BEGIN_NAMESPACE

class Model;

/**
 * @brief The SqlQueryManager class allows to create query by chaining public methods instead of writing raw sql.
 *
 * The class is meant as an interface to create query without writing raw sql. A query can be created by chaining the public
 * methods of the call that emulates sql statements. The sql is generated from within these methods and should be adaptated to
 * suit the database type (MySQL, SQLite, Postgresql...) currently used.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT SqlQueryManager
{
    SqlDatabaseStorage &connection;
    QString queryText; ///< @brief The text of the query being contructed by the manager
    CWF::SqlQuery query; ///< @brief The query being constructed
    qint32 bindingDone = 0; ///< @brief How many bindings were done with the current query ?
public:
    explicit SqlQueryManager(SqlDatabaseStorage &connection) : connection(connection), query(connection) {} ///< @brief Constructor
    /**
     * @brief reset Reset the query manager
     */
    void reset();
    /**
     * @brief createTable Construct a query to create a new table in a database
     * @param tableName The name of the table to be added
     */
    QString createTable(const QString& tableName);
    /**
     * @brief createIndex Construct a query to create a new index in the database
     * @param indexName The name of the new index
     * @param tableName The name of the table targeted
     * @param field The name of the column targeted
     * @param unique Should the index be unique ?
     */
    void createIndex(const QString& indexName, const QString& tableName, const QString& field, bool unique=false);

    SqlQueryManager& alterTable(const QString& tableName); ///< @brief Alter a table (can be chained)
    SqlQueryManager& addColumn(const QString& field, const QString& type); ///< @brief Add a column (can be chained)
    SqlQueryManager& select(const QString& what, const QString& tableName); ///< @brief Select statement (can be chained)
    SqlQueryManager& count(const QString& what, const QString& tableName); ///< @brief Count statement (can be chained)
    SqlQueryManager& insert(const QString& tableName, const QString& fields); ///< @brief Insert statement (can be chained)
    SqlQueryManager& remove(const QString& tableName, const QString& cond); ///< @brief Remove statement (can be chained)
    SqlQueryManager& update(const QString& tableName, const QString& fieldValue); ///< @brief Update statement (can be chained)
    SqlQueryManager& where(const QString& c); ///< @brief Where statement (can be chained)
    SqlQueryManager& orderBy(const QString& c); ///< @brief OrderBy statement (can be chained)
    SqlQueryManager& leftJoin(const QString& tableName, const QString& cond); ///< @brief leftJoin statement (can be chained)
    SqlQueryManager& innerJoin(const QString& tableName, const QString& cond); ///< @brief innerJoin statement (can be chained)
    SqlQueryManager& addBindValue(const QVariant& v); ///< @brief addBindValue statemnet (can be chained)
    bool prepare(); ///< @brief Prepare the query
    QJsonObject exec(); ///< @brief // Executte the query
    QJsonObject exec(const QString &sql); ///< @brief // Executte the query
    inline QJsonArray toJson() { return query.toJson(); } ///< @brief // Get the result of the query in JSON format
    /**
     * @brief textQuery Get the text of the query (raw sql)
     * @param addEndDot Should we add ";" at the end of the query if it is not present ?
     * @return QString
     */
    QString textQuery(bool addEndDot = false) const;
    /**
     * @brief prefixPropNames Create a string made of all the properties of a given model. These are all prefixed by the name of the model.
     * @param model The targeted model object
     * @return QString
     *
     * This feature is useful when building complex leftJoin request: it allows to build aliases to avoid name conflicts.
     */
    QString prefixPropNames(Model &model);

    inline QString getQueryText() const { return queryText; }
};

CWF_END_NAMESPACE

#endif // SQLQUERYMANAGER_HH

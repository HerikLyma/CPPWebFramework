#ifndef MODELBASICOPERATION_HH
#define MODELBASICOPERATION_HH

#include "sqlquery.h"
#include "sqlquerymanager.h"

#include <QSqlField>
#include <QMap>
#include <QVector>

CWF_BEGIN_NAMESPACE

/**
 * @brief The ModelBasicOperation class implements several utility functions that are used in the Model class.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT ModelBasicOperation
{
protected:
    SqlDatabaseStorage &connection;
public:
    /**
     * @brief Contructor
     */
    explicit ModelBasicOperation(SqlDatabaseStorage &connection);
    /**
      * @brief Destructor
      */
    ~ModelBasicOperation() = default;
    /**
     * @brief createTable Create a table in the database
     * @param name The name of the table to create
     * @return Bool
     */
    bool createTable(const QString &name);
    /**
     * @brief Creates a version table.
     * @return  Bool
     */
    bool createVersionTable();
    /**
     * @brief addFieldToTable Add a column in a database table
     * @param fieldName The name of the column to add
     * @param type The type of data stored in the column
     * @param tableName The name of the database table
     * @return Bool
     */
    bool addFieldToTable(const QString& fieldName, const QVariant::Type type, const QString& tableName) const;
    /**
     * @brief changeTableVersion Change the version number of a database table
     * @param tableName The name of the table
     * @param version The version to be saved
     * @return Bool
     */
    bool changeTableVersion(const QString& tableName, qint32 version) const;
    /**
     * @brief tables List all the tables of a database
     * @return QStringList: a list of all tables
     */
    inline QStringList tables() const  { return connection.getDatabase().tables(); }
    /**
     * @brief fields List all the fields of a database table
     * @param tableName The name of the database table
     * @return QStringList
     */
    QStringList fields(const QString& tableName) const;
    /**
     * @brief tableVersion Get the version of the database table
     * @param tableName The name of the database table
     * @return qint32
     */
    qint32 tableVersion(const QString& tableName) const;
    /**
     * @brief convertQVariantTypeToSQLType Convert a given type (enum) to a string representing an sql type
     * @param type The type of the data to be converted
     * @return QString
     */
    QString convertQVariantTypeToSQLType(const QVariant::Type type) const;
    /**
     * @brief save Save the data contained in a map (given as an argument) in the given database table.
     * @param tableName The name of the database table to receive a new entry
     * @param map The data to be added
     * @return qint64: The id of the new entry
     */
    qint64 save(const QString& tableName, const QMap<QString, QVariant>& map);
    /**
     * @brief buildVector Build a vector of map where each map represents an entry that was retrieved from the database
     * @param tableName The name of the database table on which the method should work
     * @param selectCondition A set of conditions to  filter the entries of the database table
     * @param props The properties to be retrieved for each selected entry
     * @param orderBy What is the order by criteria ?
     * @return QVector<QMap<QString, QVariant> >
     */
    QVector<QMap<QString, QVariant> > buildVector(const QString& tableName,
                                const QMap<QString, QVariant> &selectCondition,
                                const QStringList& props,
                                const QString &orderBy="id"
                                );

    /**
     * @brief build Construct a map of properties retrieved from a single database entry
     * @param tableName The name of the table with the entry
     * @param selectCondition The conditions used to select the entry
     * @param props The properties to retrieve from the entry
     * @return QMap<QString, QVariant>
     */
    QMap<QString, QVariant> build(const QString &tableName,
                                  const QMap<QString, QVariant> &selectCondition,
                                  const QStringList& props
                                  );

    /**
     * @brief remove Delete an entry from the database
     * @param tableName The table with the entry
     * @param id The id of the entry to be deleted
     * @return Bool
     */
    bool remove(const QString& tableName, const qint64& id);
    /**
     * @brief constructInsertTextQuery Build an insert query and return its text version
     * @param tableName The name of the table in which an insertion should be done
     * @param map The data to be inserted
     * @param values The data to be inserted but sorted to match the field order
     * @return QString
     */
    QString constructInsertTextQuery(const QString& tableName, const QMap<QString, QVariant> &map, QVector<QVariant>& values);
    /**
     * @brief constructUpdateTextQuery
     * @param tableName
     * @param map The data to be inserted
     * @param values The data to be inserted but sorted to match the field order
     * @return QString
     */
    QString constructUpdateTextQuery(const QString& tableName, const QMap<QString, QVariant> &map, QVector<QVariant>& values);
    /**
     * @brief createIndex Create an index for a given table and column
     * @param tableName The name of the table to have an index
     * @param column The name of the column (or field) which should be indexed
     * @param unique Should the index be unique and enforce this ?
     * @return Bool
     */
    bool createIndex(const QString& tableName, const QString& column, bool unique=false) const;
    /**
     * @brief isTableInDb Check if a table is present within the database
     * @param tableName The name of the table
     * @return Bool
     */
    inline bool isTableInDb(const QString &tableName) const { return connection.getDatabase().tables().contains(QLatin1String(tableName.toLatin1())); }
private:
    /**
     * @brief insertEntry Insert an entry in a database table.
     * @param tableName The name of the table to receive the data
     * @param map The data
     * @return qint64: The id of the new entry
     */
    qint64 insertEntry(const QString& tableName, const QMap<QString, QVariant>& map);
    /**
     * @brief updateEntry Update a database entry
     * @param tableName The name of the database table to be updated
     * @param map The data to be inserted in the entry. An id should be present here to select the correct entry.
     */
    qint64 updateEntry(const QString& tableName, const QMap<QString, QVariant>& map);
};

CWF_END_NAMESPACE

#endif // MODELBASICOPERATION_HH

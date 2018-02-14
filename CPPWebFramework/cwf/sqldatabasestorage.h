#ifndef SQLDATABASESTORAGE_H
#define SQLDATABASESTORAGE_H
#ifdef QT_SQL_LIB

#include <QUuid>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QThreadStorage>

/**
 * The SqlDatabaseStorage class allows you to reuse connections made to the database through the QSqlDatabase class within QThreadPool.
 */
class SqlDatabaseStorage
{    
    class Database
    {
        friend class SqlDatabaseStorage;
        QSqlDatabase *db = nullptr;
    public:
        Database() = default;
        Database(Database &other)
        {
            db = other.db;
            other.db = nullptr;
        }
        ~Database()
        {
            if(db)
            {
                const QString conName(db->connectionName());
                db->close();
                delete db;
                QSqlDatabase::removeDatabase(conName);
            }
        }
    };
    QString type;
    QString hostName;
    QString databaseName;
    QString userName;
    QString password;
    int port;
    QThreadStorage<Database> pool;
public:
    /**
     * @brief This constructor receives informations to create a connection to the database.
     * @param const QString &type : Driver type.
     * @param const QString &hostName : Sets the connection's host name to host.
     * @param const QString &databaseName : Sets the connection's database name to name.
     * @param const QString &userName : Sets the connection's user name to name.
     * @param const QString &password : Sets the connection's password to password.
     * @param int port : Sets the connection's port number to port.
     */
    SqlDatabaseStorage(const QString &type = "", const QString &hostName = "",
                       const QString &databaseName = "", const QString &userName = "",
                       const QString &password = "", int port = 0) : type(type), hostName(hostName),
                                                                    databaseName(databaseName), userName(userName),
                                                                    password(password), port(port)
    {
    }

    /**
     * @brief Returns the type.
     */
    inline QString getType() const { return type; }

    /**
     * @brief Returns the password.
     */
    inline QString getPassword() const { return password; }

    /**
     * @brief Returns the host name.
     */
    inline QString getHostName() const { return hostName; }

    /**
     * @brief Returns the database's name.
     */
    inline QString getDatabaseName() const { return databaseName; }

    /**
     * @brief Returns the user's name.
     */
    inline QString getUserName() const { return userName; }

    /**
     * @brief Returns the port.
     */
    inline int getPort() const { return port; }

    /**
     * @brief Returns the existing connection to the current thread's database. If there is no open connection to the current thread, a new connection will be created and returned.
     */
    QSqlDatabase &getDatabase()
    {
        if(!pool.hasLocalData())
        {
            Database database;
            database.db = new QSqlDatabase(QSqlDatabase::addDatabase(type, QUuid::createUuid().toString()));
            database.db->setHostName(hostName);
            database.db->setDatabaseName(databaseName);
            database.db->setPort(port);
            database.db->setUserName(userName);
            database.db->setPassword(password);
            if(!database.db->open())
                qDebug() << database.db->lastError().text();
            pool.setLocalData(database);
        }
        return *pool.localData().db;
    }
};

#endif
#endif // SQLDATABASESTORAGE_H

/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef SQLDATABASESTORAGE_H
#define SQLDATABASESTORAGE_H
#include <iostream>
#include <QUuid>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QThreadStorage>
#include "cppwebframework_global.h"

#if __cplusplus >= 201703L
#include <optional>
#endif
#if __cplusplus == 201402L
#include <experimental/optional>
#endif
CWF_BEGIN_NAMESPACE
/**
 * @brief The SqlDatabaseStorage class allows you to reuse connections made to the database through the QSqlDatabase class within QThreadPool.
 */

class CPPWEBFRAMEWORKSHARED_EXPORT SqlDatabaseStorage
{    
    class Database
    {
        friend class SqlDatabaseStorage;
        //Map database connection names the library user uses to database connection names
        //which are valid for this thread
        std::map<QString, QString> trivialNameToUniqueID;
#if __cplusplus == 201402L
        std::experimental::optional<QSqlDatabase> DBConnection; //C++ 14 Compatablity
#endif
#if __cplusplus >= 201703L
        std::optional<QSqlDatabase> DBConnection;
#endif
    public:
        Database() = default;
        Database(Database &other)
        {
            DBConnection = other.DBConnection;
            trivialNameToUniqueID = other.trivialNameToUniqueID;
            qDebug() << "Database Constructed";
        }
        ~Database()
        {
            qDebug() << "Database Destructed";
            if(DBConnection)
            {
                const QString conName(DBConnection->connectionName());

                DBConnection->close();
                 //Remove all Database connnections this thread has and which will become invalid
                for (auto const & ConnectionNamePair : trivialNameToUniqueID) {
                    DBConnection = QSqlDatabase::database(ConnectionNamePair.second, false);
                    DBConnection->close();
                    qDebug() << ConnectionNamePair.first << ConnectionNamePair.second;
                    QSqlDatabase::removeDatabase(ConnectionNamePair.second);
                }
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
        if(!pool.hasLocalData()) //Pool has no Local Data -> create DataBaseConnection
        {
            Database database;
            QString UniqueID = QUuid::createUuid().toString();
            database.DBConnection = QSqlDatabase(QSqlDatabase::addDatabase(type, UniqueID));
            database.DBConnection->setHostName(hostName);
            database.DBConnection->setDatabaseName(databaseName);
            database.DBConnection->setPort(port);
            database.DBConnection->setUserName(userName);
            database.DBConnection->setPassword(password);
            if (!database.DBConnection->open()) {
                qDebug() << database.DBConnection->lastError().text();
            }
            pool.setLocalData(database);
            pool.localData().trivialNameToUniqueID.insert({databaseName, UniqueID});
        } else { //Pool has Local Data
            auto PublicDBName = pool.localData().trivialNameToUniqueID.find(databaseName);
            QString NameOfDBConnectionToThread;
            QString UniqueConnectionName;

            if (PublicDBName != pool.localData().trivialNameToUniqueID.end()) {
                // this thread has a Connection to the Database
                if (PublicDBName->second == pool.localData().DBConnection->connectionName()) {
                    //already right connection
                } else {
                    //set the right connection
                    NameOfDBConnectionToThread = PublicDBName->first;
                    UniqueConnectionName = PublicDBName->second;
                    //pool.localData().DBConnection->close();
                    pool.localData().DBConnection = QSqlDatabase::database(UniqueConnectionName, false);
                    pool.localData().DBConnection->setHostName(hostName);
                    pool.localData().DBConnection->setDatabaseName(databaseName);
                    pool.localData().DBConnection->setPort(port);
                    pool.localData().DBConnection->setUserName(userName);
                    pool.localData().DBConnection->setPassword(password);
                    if(!pool.localData().DBConnection->open()) {
                        qDebug() << pool.localData().DBConnection->lastError().text();
                    }
                }
            } else {
                //make new Database connection for this thread
                QString UniqueID = QUuid::createUuid().toString();
                pool.localData().DBConnection->close();
                pool.localData().DBConnection = QSqlDatabase(QSqlDatabase::addDatabase(type, UniqueID));
                pool.localData().DBConnection->setHostName(hostName);
                pool.localData().DBConnection->setDatabaseName(databaseName);
                pool.localData().DBConnection->setPort(port);
                pool.localData().DBConnection->setUserName(userName);
                pool.localData().DBConnection->setPassword(password);
                if (!pool.localData().DBConnection->open()) {
                    qDebug() << pool.localData().DBConnection->lastError().text();
                }
                pool.localData().trivialNameToUniqueID.insert({databaseName, UniqueID});
            }
        }
        std::cerr << "Name To ID Mapping";
        for ( auto const & foo : pool.localData().trivialNameToUniqueID) {
            std::cerr << "Name " << foo.first.toStdString()
                      << "\tID " << foo.second.toStdString()
                      << "\n";
        }
        return pool.localData().DBConnection.value();
    }
};

CWF_END_NAMESPACE

#endif // SQLDATABASESTORAGE_H

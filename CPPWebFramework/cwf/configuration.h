/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QSettings>
#include <QHostAddress>
#include "filemanager.h"
#include "cppwebframework_global.h"
/**
 * @brief All classes of C++ Web Framework are contained within the namespace CWF.
 */
CWF_BEGIN_NAMESPACE
/**
 * @brief This class is responsable to read a ini file and extract its information.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT Configuration
{
    bool valid                = false;
    bool accessCPPWebIni      = false;
    bool accessServerPages    = false;
    int timeOut               = 30000;
    int sessionExpirationTime = 1800000;
    int cleanupInterval       = 86400000;
    int port                  = 8080;
    int maxThread             = 100;
    QString sslKeyFile;
    QString sslCertFile;
    QString path;
    QString logFilePath;
    QString indexPage;
    QHostAddress host;
    qint64 maxUploadFile = 2097152;
    qint64 maxLogFile    = 20000000;
    void configure();
public:
    /**
     * @brief Will make reading the CPPWeb.ini file and extract all of its properties.
     * @param QString serverFilesPath : You should always points to the directory server.
     * @par Example
     * @code
     * #include <QCoreApplication>
     * #include <cwf/cppwebapplication.h>
     *
     * int main(int argc, char *argv[])
     * {     
     *     CWF::CppWebApplication a(argc, argv, "PATH_TO_SERVER_FOLDER");
     *     return a.start();
     * }
     * @endcode
     */
    explicit Configuration(const QString &serverFilesPath = "");   
    /**
     * @brief Returns the timeOut property that will be used by the server to expire threads that are not in use.
     * Such threads will be restarted as needed. The default timeOut is 30000 milliseconds (30 seconds).
     * If timeOut is negative, newly created threads will not expire, e.g., they will not exit until the thread pool is destroyed.
     * @param int : Time in milliseconds.
     */
    inline int getTimeOut() const { return timeOut; }
    /**
     * @brief Returns the Session Expiration Time.
     * @param int : Time in milliseconds.
     */
    inline int getSessionExpirationTime() const { return sessionExpirationTime; }
    /**
     * @brief Returns the clean up interval Time.
     * @param int : Time in milliseconds.
     */
    inline int getCleanupInterval() const { return cleanupInterval; }
    /**
     * @brief Returns the port number.
     * @param int : port.
     */
    inline int getPort() const { return port; }
    /**
     * @brief Returns the address.
     * @param QHostAddress : host.
     */
    inline QHostAddress getHost() const { return host; }   
    /**
     * @brief Returns the max thread number.
     * @param int : max.
     */
    inline int getMaxThread() const { return maxThread; }
    /**
     * @brief Returns the ssl key file.
     * @param QString : sslKeyFile name.
     */
    inline QString getSslKeyFile() const { return sslKeyFile; }
    /**
     * @brief Returns the ssl cert file.
     * @param QString : sslCertFile name.
     */
    inline QString getSslCertFile() const { return sslCertFile; }
    /**
     * @brief Returns the path to the server's folder.
     * @param QString : path.
     */
    inline QString getPath() const { return path; }
    /**
     * @brief Returns the log file path.
     * @param QString : log file.
     */
    inline QString getLogFilePath() const { return logFilePath; }
    /**
     * @brief Returns max upload file size supported by the server.
     * @param qint64: max file size.
     */
    inline qint64 getMaxUploadFile() const { return maxUploadFile; }
    /**
     * @brief getMaxLogFile the max file log
     * @return qint64 : Max file log in bytes.
     */
    inline qint64 getMaxLogFile() const { return maxLogFile; }
    /**
     * @brief Returns the index page.
     * @return QString : index page name.
     */
    inline QString getIndexPage() const { return indexPage; }
    /**
     * @brief Returns the access server page.
     * @return bool : Access server pages.
     */
    inline bool getAccessServerPages() const { return accessServerPages; }
    /**
     * @brief Returns true if the Configuration is ok. Otherwise returns false.
     * @param bool : is valid.
     */
    inline bool isValid() const { return valid; }
};

CWF_END_NAMESPACE

#endif // CONFIGURATION_H

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
#include "filter.h"
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
    friend class CppWebServer;
    friend class HttpServletResponse;
    friend class HttpSession;
    friend class HttpReadRequest;
    friend class CppWebApplication;
    friend class FilterChain;
private:
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
    QString domain;
    QString logFilePath;
    QString indexPage;
    QHostAddress host;
    qint64 maxUploadFile = 2097152;
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
     *     CWF::Configuration configuration("/home/herik/CPPWebFramework/CPPWebFramework/server/");
     *     CWF::CppWebApplication a(argc, argv, configuration);
     *
     *     return a.start();
     * }
     * @endcode
     */
    explicit Configuration(QString serverFilesPath = "");
    /**
     * @brief Returns the timeOut property that will be used by the server to expire threads that are not in use.
     * Such threads will be restarted as needed. The default timeOut is 30000 milliseconds (30 seconds).
     * If timeOut is negative, newly created threads will not expire, e.g., they will not exit until the thread pool is destroyed.
     * @param int : Time in milliseconds.
     */
    int getTimeOut() const;
    /**
     * @brief Set the timeOut property.
     * @param int value : New timeOut value in Milliseconds.
     */
    void setTimeOut(int value);
    /**
     * @brief Returns the time that a session takes to expire. The default is 1800000(ms).
     * @param int : Time in milliseconds.
     */
    int getSessionExpirationTime() const;
    /**
     * @brief Set the sessionExpirationTime property.
     * @param int value : New sessionExpirationTime value in Milliseconds.
     */
    void setSessionExpirationTime(int value);
    /**
     * @brief Returns the cleanupInterval that indicates how often the server will perform the cleanup of expired sessions.
     * @param int : Time in milliseconds.
     */
    int getCleanupInterval() const;
    /**
     * @brief Set the cleanupInterval property that will be used by the server. The default is 86400000(ms).
     * @param int : Time in milliseconds.
     */
    void setCleanupInterval(int value);
    /**
     * @brief Returns the port number that will be used by the server. The default is 8080.
     * @return int : Port number.
     */
    int getPort() const;
    /**
     * @brief Set the port number property.
     * @param int value : Port number.
     */
    void setPort(int value);
    /**
     * @brief Returns the port number that will be used by the server. The default is 127.0.0.1.
     * @return QHostAddress : Host address.
     */
    QHostAddress getHost() const;
    /**
     * @brief Set the host property.
     * @param const QHostAddress &value : Host address.
     */
    void setHost(const QHostAddress &value);
    /**
     * @brief Returns the maximum number of threads that can be created by the server. The default is 100.
     * @return int : Maximum number of threads.
     */
    int getMaxThread() const;
    /**
     * @brief Set the maxThread property.
     * @param int value : Maximum number of threads.
     */
    void setMaxThread(int value);
    /**
     * @brief Retuns the sslKeyFile name property that can be used by the server to make the SSL configuration.
     * @return QString : SSL Key File name.
     */
    QString getSslKeyFile() const;
    /**
     * @brief Set the sslKeyFile name property.
     * @param const QString &value : SSL Key File name.
     */
    void setSslKeyFile(const QString &value);
    /**
     * @brief Retuns the sslCertFile name property that can be used by the server to make the SSL configuration.
     * @return QString : SSL Cert File name.
     */
    QString getSslCertFile() const;
    /**
     * @brief Set the sslCertFile name property.
     * @param const QString &value : SSL Cert File name.
     */
    void setSslCertFile(const QString &value);
    /**
     * @brief Returns the path should point to the server folder.
     * @return QString : Path.
     */
    QString getPath() const;
    /**
     * @brief Set the path property.
     * @param const QString &value :
     */
    void setPath(const QString &value);
    /**
     * @brief Returns the applications domain name
     * @return QString : Domain name.
     */
    QString getDomain() const;
    /**
     * @brief Set domain property.
     * @param value :
     */
    void setDomain(const QString &value);
    /**
     * @brief Returns the path to the log file and must to be relative to the path set in the "path".
     * @return QString : Log File Path.
     */
    QString getLogFilePath() const;
    /**
     * @brief Set the logFilePath property.
     * const QString &value : Log file path.
     */
    void setLogFilePath(const QString &value);
    /**
     * @brief Returns the maximum upload file size in bytes.
     * @return qint64 : Max upload file size in bytes.
     */
    qint64 getMaxUploadFile() const;
    /**
     * @brief Set maxUploadFile property in bytes.
     * @param const qint64 &value : Max upload file size in bytes.
     */
    void setMaxUploadFile(const qint64 &value);
};

CWF_END_NAMESPACE

#endif // CONFIGURATION_H

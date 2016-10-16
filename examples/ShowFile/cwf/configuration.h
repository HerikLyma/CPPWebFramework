/**
  @file configuration.h
  @author Herik Lima
*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QSettings>
#include <QHostAddress>
#include "filter.h"
#include "filemanager.h"

namespace CWF
{
    class Configuration
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
        QString suffix;
        QHostAddress host;
        QMap<QString, HttpServlet *> urlServlet;
        qint64 maxUploadFile = 2097152;
    public:
        Configuration(QString serverFilesPath = "");
        int getTimeOut() const;
        void setTimeOut(int value);
        int getSessionExpirationTime() const;
        void setSessionExpirationTime(int value);
        int getCleanupInterval() const;
        void setCleanupInterval(int value);
        int getPort() const;
        void setPort(int value);
        int getMaxThread() const;
        void setMaxThread(int value);
        QString getSslKeyFile() const;
        void setSslKeyFile(const QString &value);
        QString getSslCertFile() const;
        void setSslCertFile(const QString &value);
        QString getPath() const;
        void setPath(const QString &value);
        QString getDomain() const;
        void setDomain(const QString &value);
        QString getLogFilePath() const;
        void setLogFilePath(const QString &value);
        QHostAddress getHost() const;
        void setHost(const QHostAddress &value);
        QMap<QString, HttpServlet *> getUrlServlet() const;
        void setUrlServlet(const QMap<QString, HttpServlet *> &value);
        QString getServerConfig() const;
        void setServerConfig(const QString &value);
        qint64 getMaxUploadFile() const;
        void setMaxUploadFile(const qint64 &value);
    };
}

#endif // CONFIGURATION_H

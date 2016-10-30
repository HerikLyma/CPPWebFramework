/**
  @file configuration.cpp
  @author Herik Lima
*/

#include "configuration.h"

namespace CWF
{
    Configuration::Configuration(QString serverFilesPath)
    {
        if(!serverFilesPath.isEmpty())
        {
            FileManager().removeLastBar(serverFilesPath);
            serverFilesPath += "/config/CPPWeb.ini";
            QSettings settings(serverFilesPath, QSettings::Format::IniFormat);
            settings.beginGroup("config");
            host                  = settings.value("host").toString();
            port                  = settings.value("port").toInt();
            maxThread             = settings.value("maxThread").toInt();
            cleanupInterval       = settings.value("cleanupInterval").toInt();
            timeOut               = settings.value("timeOut").toInt();
            sslKeyFile            = settings.value("sslKeyFile").toString();
            sslCertFile           = settings.value("sslCertFile").toString();
            sessionExpirationTime = settings.value("sessionExpirationTime").toInt();
            logFilePath           = settings.value("logFilePath").toString();
            path                  = settings.value("path").toString();
            maxUploadFile         = settings.value("maxUploadFile").toLongLong();
            indexPage             = settings.value("indexPage").toString();
            accessCPPWebIni       = settings.value("accessCPPWebIni").toBool();
            suffix                = settings.value("suffix").toString();
            accessServerPages     = settings.value("accessServerPages").toBool();

            FileManager fileManager;
            fileManager.removeLastBar(path);
            fileManager.removeFirstBar(sslCertFile);
            fileManager.removeFirstBar(sslKeyFile);
            fileManager.removeFirstBar(logFilePath);
            fileManager.removeLastBar(logFilePath);
            logFilePath = path + "/" + logFilePath;

            if(!sslKeyFile.isEmpty())
                sslKeyFile           = path + "/" + sslKeyFile;
            if(!sslCertFile.isEmpty())
                sslCertFile          = path + "/" + sslCertFile;
        }
    }

    int Configuration::getTimeOut() const
    {
        return timeOut;
    }

    void Configuration::setTimeOut(int value)
    {
        timeOut = value;
    }

    int Configuration::getSessionExpirationTime() const
    {
        return sessionExpirationTime;
    }

    void Configuration::setSessionExpirationTime(int value)
    {
        sessionExpirationTime = value;
    }

    int Configuration::getCleanupInterval() const
    {
        return cleanupInterval;
    }

    void Configuration::setCleanupInterval(int value)
    {
        cleanupInterval = value;
    }

    int Configuration::getPort() const
    {
        return port;
    }

    void Configuration::setPort(int value)
    {
        port = value;
    }

    int Configuration::getMaxThread() const
    {
        return maxThread;
    }

    void Configuration::setMaxThread(int value)
    {
        maxThread = value;
    }

    QString Configuration::getSslKeyFile() const
    {
        return sslKeyFile;
    }

    void Configuration::setSslKeyFile(const QString &value)
    {
        sslKeyFile = value;
    }

    QString Configuration::getSslCertFile() const
    {
        return sslCertFile;
    }

    void Configuration::setSslCertFile(const QString &value)
    {
        sslCertFile = value;
    }

    QString Configuration::getPath() const
    {
        return path;
    }

    void Configuration::setPath(const QString &value)
    {
        path = value;
    }

    QString Configuration::getDomain() const
    {
        return domain;
    }

    void Configuration::setDomain(const QString &value)
    {
        domain = value;
    }

    QString Configuration::getLogFilePath() const
    {
        return logFilePath;
    }

    void Configuration::setLogFilePath(const QString &value)
    {
        logFilePath = value;
    }

    QHostAddress Configuration::getHost() const
    {
        return host;
    }

    void Configuration::setHost(const QHostAddress &value)
    {
        host = value;
    }

    qint64 Configuration::getMaxUploadFile() const
    {
        return maxUploadFile;
    }

    void Configuration::setMaxUploadFile(const qint64 &value)
    {
        maxUploadFile = value;
    }
}

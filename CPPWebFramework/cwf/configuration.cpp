/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "configuration.h"
#include "constants.h"
#include <QDir>

CWF_BEGIN_NAMESPACE

qint64 Configuration::getMaxLogFile() const
{
    return maxLogFile;
}

void Configuration::setMaxLogFile(const qint64 &value)
{
    maxLogFile = value;
}

Configuration::Configuration(const QString &serverFilesPath)
{            
    path = serverFilesPath;
    FileManager::removeLastBar(path);
    const QString iniFile("/config/CPPWeb.ini");
    if(QFile(path + iniFile).exists())
    {
        valid = true;
        configure();
    }
    else
    {
        path = QDir::currentPath() + "/server";
        if(QFile(path + iniFile).exists())
        {
            valid = true;
            configure();
        }
        else
        {
            valid = false;
        }
    }
}

void Configuration::configure()
{
    const QString iniFile(path + "/config/CPPWeb.ini");
    if(valid)
    {
        QSettings settings(iniFile, QSettings::Format::IniFormat);
        settings.beginGroup("config");
        host.setAddress(settings.value("host").toString());
        port                  = settings.value("port").toInt();
        maxThread             = settings.value("maxThread").toInt();
        cleanupInterval       = settings.value("cleanupInterval").toInt();
        timeOut               = settings.value("timeOut").toInt();
        sslKeyFile            = settings.value("sslKeyFile").toString();
        sslCertFile           = settings.value("sslCertFile").toString();
        sessionExpirationTime = settings.value("sessionExpirationTime").toInt();
        maxUploadFile         = settings.value("maxUploadFile").toLongLong();
        indexPage             = settings.value("indexPage").toString();
        accessCPPWebIni       = settings.value("accessCPPWebIni").toBool();
        accessServerPages     = settings.value("accessServerPages").toBool();
        maxLogFile            = settings.value("maxLogFile").toLongLong();
        logFilePath = path + "/config/log/CPPWebServer.log";

        FileManager::removeFirstBar(sslCertFile);
        FileManager::removeFirstBar(sslKeyFile);
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

bool Configuration::isValid() const
{
    return valid;
}

CWF_END_NAMESPACE

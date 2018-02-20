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

CWF_END_NAMESPACE

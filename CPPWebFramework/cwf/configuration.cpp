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

QSsl::KeyAlgorithm extractSslKeyAlgorithm(QString value)
{
    value = value.trimmed().toLower();
    if(value.startsWith("opaque"))
        return QSsl::Opaque;
    if(value.startsWith("dsa"))
        return QSsl::Dsa;
    if(value.startsWith("ec"))
        return QSsl::Dsa;
    return QSsl::Rsa;
}

QSsl::EncodingFormat extractSslEncodingFormat(QString value)
{
    value = value.trimmed().toLower();
    if(value.startsWith("der"))
        return QSsl::Der;
    return QSsl::Pem;
}

QSsl::KeyType extractSslKeyType(QString value)
{
    value = value.trimmed().toLower();
    if(value.startsWith("publickey"))
        return QSsl::PublicKey;
    return QSsl::PrivateKey;
}

QSslSocket::PeerVerifyMode extractSslPeerVerifyMode(QString value)
{
    value = value.trimmed().toLower();
    if(value.startsWith("querypeer"))
        return QSslSocket::QueryPeer;
    if(value.startsWith("verifypeer"))
        return QSslSocket::QueryPeer;
    if(value.startsWith("autoverifypeer"))
        return QSslSocket::QueryPeer;
    return QSslSocket::VerifyNone;
}


QSsl::SslProtocol extractSslProtocol(QString value)
{
    value = value.trimmed().toLower();
    if(value.startsWith("sslv3"))
        return QSsl::SslV3;
    if(value.startsWith("sslv2"))
        return QSsl::SslV2;
    if(value.startsWith("tlsv1_0"))
        return QSsl::TlsV1_0;
    if(value.startsWith("tlsv1_1"))
        return QSsl::TlsV1_1;
    if(value.startsWith("tlsv1_2"))
        return QSsl::TlsV1_2;
    if(value.startsWith("anyprotocol"))
        return QSsl::AnyProtocol;
    if(value.startsWith("secureprotocols"))
        return QSsl::SecureProtocols;
    if(value.startsWith("tlsv1_0Orlater"))
        return QSsl::TlsV1_1OrLater;
    if(value.startsWith("tlsv1_2Orlater"))
        return QSsl::TlsV1_2OrLater;
    if(value.startsWith("unknownprotocol"))
        return QSsl::UnknownProtocol;
    return QSsl::TlsV1SslV3;
}


void Configuration::configure()
{
    const QString iniFile(path + "/config/CPPWeb.ini");
    if(valid)
    {
        QSettings settings(iniFile, QSettings::Format::IniFormat);
        settings.beginGroup("config");
        host.setAddress(settings.value("host").toString());
        port                  = static_cast<quint16>(settings.value("port").toInt());
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
        sslPassPhrase         = settings.value("sslPassPhrase").toByteArray();
        sslKeyAlgorithm       = extractSslKeyAlgorithm(settings.value("sslKeyAlgorithm").toString());
        sslEncodingFormat     = extractSslEncodingFormat(settings.value("sslEncodingFormat").toString());
        sslKeyType            = extractSslKeyType(settings.value("sslKeyType").toString());
        sslPeerVerifyMode     = extractSslPeerVerifyMode(settings.value("sslPeerVerifyMode").toString());
        sslProtocol           = extractSslProtocol(settings.value("sslProtocol").toString());
        logFilePath           = path + "/config/log/CPPWebServer.log";

        FileManager::removeFirstBar(sslCertFile);
        FileManager::removeFirstBar(sslKeyFile);
        if(!sslKeyFile.isEmpty())
            sslKeyFile           = path + "/" + sslKeyFile;
        if(!sslCertFile.isEmpty())
            sslCertFile          = path + "/" + sslCertFile;
    }
}

CWF_END_NAMESPACE

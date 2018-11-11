#include "sslloader.h"
#include <QFile>
#include <QDebug>
#include <QSslKey>
#include <QSslCertificate>
#include <QSslConfiguration>
#include <utility>

CWF_BEGIN_NAMESPACE

SslLoader::SslLoader(Configuration configuration) : configuration(std::move(configuration))
{
}

QByteArray getFileContent(const QString &fileName, bool &ok)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        ok = true;
        return file.readAll();
    }
    ok = false;
    qDebug() << "Can't open " << fileName << ": " << file.errorString();
    return QByteArray();
}

QSslConfiguration *buildSslConfiguration(const QSslKey &keySsl,
                                         const QSslCertificate &certificateSsl,
                                         const Configuration &configuration)
{
    auto *temp = new QSslConfiguration;
    temp->setProtocol(configuration.getSslProtocol());
    temp->setPeerVerifyMode(configuration.getSslPeerVerifyMode());
    temp->setPrivateKey(keySsl);
    temp->setLocalCertificate(certificateSsl);
    return temp;
}

QSslConfiguration *SslLoader::getSslConfiguration() const
{
#ifdef QT_NO_SSL
    qDebug() << "Secure Sockets Layer (SSL) is not supported, please check your configuration.";
    return nullptr;
#else
    if(!configuration.getSslKeyFile().isEmpty() && !configuration.getSslCertFile().isEmpty())
    {
        bool okKey, okCert;
        QByteArray myKeyStr(getFileContent(configuration.getSslKeyFile(), okKey));
        QByteArray myCertificateStr(getFileContent(configuration.getSslCertFile(), okCert));

        if(!okKey || !okCert)
        {
            return nullptr;
        }

        QSslKey keySsl(myKeyStr,
                       configuration.getSslKeyAlgorithm(),
                       configuration.getSslEncodingFormat(),
                       configuration.getSslKeyType(),
                       configuration.getSslPassPhrase());

        QSslCertificate certificateSsl(myCertificateStr,
                                       configuration.getSslEncodingFormat());

        if(keySsl.isNull())
        {
            qDebug() << "Invalid SLL key file, please check the CPPWeb.ini file.";
            return nullptr;
        }
        if(certificateSsl.isNull())
        {
            qDebug() << "Invalid SLL cert file, please check the CPPWeb.ini file.";
            return nullptr;
        }

        return buildSslConfiguration(keySsl, certificateSsl, configuration);
    }
#endif
    return nullptr;
}

CWF_END_NAMESPACE

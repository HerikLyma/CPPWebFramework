/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cppwebserver.h"
#include <QtConcurrent/QtConcurrent>

CWF_BEGIN_NAMESPACE

CppWebServer::CppWebServer(const Configuration &configuration, Filter *filter) : configuration(configuration), filter(filter)
{
    loadSslConfiguration();
    this->thread()->setPriority(QThread::TimeCriticalPriority);
    pool.setMaxThreadCount(configuration.getMaxThread());
    pool.setExpiryTimeout(configuration.getTimeOut());
    if(!filter)
        this->filter = new Filter;
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(doClean()));
    timer->start(configuration.getCleanupInterval());
}

CppWebServer::~CppWebServer()
{
    while(!pool.waitForDone());
    for(QMapThreadSafety<QString, HttpServlet*>::iterator it = urlServlet.begin(); it != urlServlet.end(); ++it)
    {
        HttpServlet *o = it.value();
        if(o != nullptr)
        {
            delete o;
            o = nullptr;
        }
    }

    for(QMapThreadSafety<QString, HttpSession*>::iterator it = sessions.begin(); it != sessions.end(); ++it)
    {
        HttpSession *o = it.value();
        if(o != nullptr)
        {
            delete o;
            o = nullptr;
        }
    }

    delete filter;
    if(sslConfiguration)
        delete sslConfiguration;
}

void CppWebServer::incomingConnection(qintptr socketfd)
{
    while(block)
        this->thread()->msleep(sleepTime);   
    pool.start(new HttpReadRequest(socketfd, urlServlet, sessions, configuration, sslConfiguration, filter));
}

void CppWebServer::doClean()
{    
    block = 1;
    while(!pool.waitForDone(sleepTime));

    HttpSession *session = nullptr;
    QStringList idSessionsToDelete;
    for(auto it = sessions.begin(); it != sessions.end(); ++it)
    {
        session = it.value();
        if(session->isExpired())
        {
            idSessionsToDelete.push_back(session->getId());
            delete session;
        }
    }
    for(int i = 0; i < idSessionsToDelete.size(); ++i)
        sessions.remove(idSessionsToDelete[i]);

    block = 0;
}

void CppWebServer::loadSslConfiguration()
{
    QString sslKey  = configuration.getSslKeyFile();
    QString sslCert = configuration.getSslCertFile();
    if (!sslKey.isEmpty() && !sslCert.isEmpty())
    {
#ifdef QT_NO_OPENSSL
            qDebug() << "SSL is not supported";
            return;
#else
            QFile certFile(sslCert);
            QFile keyFile(sslKey);

            if(!certFile.open(QIODevice::ReadOnly))
            {
                qDebug() << "Can't open SSL Cert File";
                return;
            }
            if(!keyFile.open(QIODevice::ReadOnly))
            {
                qDebug() << "Can't open SSL Key File";
                return;
            }

            QSslCertificate certificate(&certFile, QSsl::Pem);
            QSslKey key(&keyFile, QSsl::Rsa, QSsl::Pem);
            keyFile.close();
            certFile.close();

            if(key.isNull())
            {
                qDebug() << "Invalid SLL Key File";
                return;
            }
            else if(certificate.isNull())
            {
                qDebug() << "Invalid SLL Cert File";
                return;
            }

            sslConfiguration = new QSslConfiguration();

            sslConfiguration->setLocalCertificate(certificate);
            sslConfiguration->setPrivateKey(key);
            sslConfiguration->setPeerVerifyMode(QSslSocket::VerifyNone);
            sslConfiguration->setProtocol(QSsl::TlsV1SslV3);
#endif
    }
}

CWF_END_NAMESPACE

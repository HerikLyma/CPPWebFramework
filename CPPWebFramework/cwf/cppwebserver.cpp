/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cppwebserver.h"
#include "sslloader.h"

CWF_BEGIN_NAMESPACE

CppWebServer::CppWebServer(const Configuration &configuration, Filter *filter) : configuration(configuration), filter(filter)
{
    ssl = SslLoader(configuration).getSslConfiguration();
    this->thread()->setPriority(QThread::TimeCriticalPriority);
    pool.setMaxThreadCount(configuration.getMaxThread());
    pool.setExpiryTimeout(configuration.getTimeOut());
    if(!filter)
    {
        this->filter = new Filter;
    }
    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &CppWebServer::doClean);
    timer->start(configuration.getCleanupInterval());
}

CppWebServer::~CppWebServer()
{
    while(!pool.waitForDone());

    std::for_each(urlController.constBegin(), urlController.constEnd(), [](Controller *i){ delete i; });
    std::for_each(sessions.constBegin(), sessions.constEnd(), [](Session *i){ delete i; });
    delete filter;
    delete ssl;
}

void CppWebServer::incomingConnection(qintptr socketfd)
{
    while(block)
    {
        this->thread()->msleep(static_cast<unsigned long>(sleepTime));
    }
    pool.start(new HttpReadRequest(socketfd, urlController, sessions, configuration, ssl, filter), QThread::LowPriority);
}

void CppWebServer::doClean()
{    
    block = 1;
    while(!pool.waitForDone(sleepTime));

    Session *session = nullptr;
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
    {
        sessions.remove(idSessionsToDelete[i]);
    }

    block = 0;
}


CWF_END_NAMESPACE

/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "httpsession.h"
#include "configuration.h"

CWF_BEGIN_NAMESPACE

HttpSession::HttpSession(const QString &id, qint64 sessionTimeOut) : id(id),
    sessionTimeOut(sessionTimeOut),
    autoClearAttributes(false),
    expired (false)
{    
}

HttpSession::~HttpSession()
{
    QMutexLocker locker(&mutex);
    if(autoClearAttributes)
    {
        for(QMapThreadSafety<QString, QObject*>::iterator it = attributes.begin(); it != attributes.end(); ++it)
        {
            QObject *o = it.value();
            if(o != nullptr)
                delete o;
        }
    }
}

QObject *HttpSession::getAttribute(const QString &name) const
{
    if(attributes.contains(name))
        return attributes[name];
    return nullptr;
}

QStringList HttpSession::getAttributeNames()
{    
    QStringList list;
    for(QMapThreadSafety<QString, QObject*>::iterator it = attributes.begin(); it != attributes.end(); ++it)
        list.push_back(it.key());
    return list;
}

QString HttpSession::getId() const
{
    QMutexLocker locker(&mutex);
    return id;
}

void HttpSession::validate()
{
    QMutexLocker locker(&mutex);
    expired = 0;
    qint64 currentTime     = QDateTime::currentMSecsSinceEpoch();
    lastAccessedTime       = currentTime;
    sessionExpirationTime  = currentTime + sessionTimeOut;
}

bool HttpSession::isExpired()
{
    QMutexLocker locker(&mutex);
    if(!expired)
    {
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        expired = currentTime >= sessionExpirationTime;
    }
    return expired;
}

void HttpSession::setSessionTimeOut(qint64 value)
{
    if(value >= 0)
    {
        sessionTimeOut = value;
    }
}

CWF_END_NAMESPACE

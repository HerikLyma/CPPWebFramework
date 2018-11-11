/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "session.h"

#include <utility>
#include "configuration.h"

CWF_BEGIN_NAMESPACE

Session::Session(QString id, qint64 sessionTimeOut) : id(std::move(id)),
    sessionTimeOut(sessionTimeOut),
    autoClearAttributes(false),
    expired (false)
{    
}

Session::~Session()
{
    QMutexLocker locker(&mutex);
    if(autoClearAttributes)
    {
        for(QMapThreadSafety<QString, QObject*>::iterator it = attributes.begin(); it != attributes.end(); ++it)
        {
            delete it.value();
        }
    }
}

QStringList Session::getAttributeNames()
{    
    QStringList list;
    for(QMapThreadSafety<QString, QObject*>::iterator it = attributes.begin(); it != attributes.end(); ++it)
        list.push_back(it.key());
    return list;
}

QString Session::getId() const
{
    QMutexLocker locker(&mutex);
    return id;
}

void Session::validate()
{
    QMutexLocker locker(&mutex);
    expired = 0;
    qint64 currentTime     = QDateTime::currentMSecsSinceEpoch();
    lastAccessedTime       = currentTime;
    sessionExpirationTime  = currentTime + sessionTimeOut;
}

bool Session::isExpired()
{
    QMutexLocker locker(&mutex);
    if(!expired)
    {
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        expired = currentTime >= sessionExpirationTime;
    }
    return expired;
}

void Session::setSessionTimeOut(qint64 value)
{
    if(value >= 0)
    {
        sessionTimeOut = value;
    }
}

CWF_END_NAMESPACE

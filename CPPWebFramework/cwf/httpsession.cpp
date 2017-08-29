/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "httpsession.h"
#include "configuration.h"

CWF_BEGIN_NAMESPACE

extern const Configuration configuration;
HttpSession::HttpSession(const QString &id) : id(id),
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

qint64 HttpSession::getCreationTime() const
{    
    return creationTime;
}

QString HttpSession::getId() const
{
    QMutexLocker locker(&mutex);
    return id;
}

qint64 HttpSession::getLastAccessedTime() const
{    
    return lastAccessedTime;
}

void HttpSession::validate()
{
    QMutexLocker locker(&mutex);
    expired = 1;
    qint64 currentTime     = QDateTime::currentMSecsSinceEpoch();
    lastAccessedTime       = currentTime;
    sessionExpirationTime  = currentTime + configuration.sessionExpirationTime;
}

void HttpSession::invalidate()
{    
    expired = 1;
}

int HttpSession::removeAttribute(const QString &name)
{
    return attributes.remove(name);
}

void HttpSession::addAttribute(const QString &name, QObject *value)
{
    attributes.insert(name, value);
}

bool HttpSession::getAutoClearAttributes() const
{    
    return autoClearAttributes;
}

void HttpSession::setAutoClearAttributes(bool value)
{    
    autoClearAttributes = value;
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

CWF_END_NAMESPACE

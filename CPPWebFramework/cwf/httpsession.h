/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef HTTPSESSION_H
#define HTTPSESSION_H

#include <QMap>
#include "httpcookie.h"
#include <atomic>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QStringList>
#include <QMutexLocker>
#include "qmapthreadsafety.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE

class Configuration;
class HttpServletRequest;

/**
 * @brief The HttpSession class holds information about a client session.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT HttpSession
{
    friend class HttpReadRequest;
    friend class HttpServletRequest;
    QString id;
    QAtomicInteger<qint64> sessionTimeOut;
    QAtomicInteger<qint64> creationTime;
    QAtomicInteger<qint64> lastAccessedTime;
    QAtomicInteger<qint64> sessionExpirationTime;
    QAtomicInteger<qint64> timeOut;
    QAtomicInteger<qint8>  autoClearAttributes = 0;
    QAtomicInteger<qint8>  expired = 0;
    QMapThreadSafety<QString, QObject*> attributes;
    mutable QMutex mutex;
public:
    /**
     * @brief Construct a session with a unique identifier
     */
    explicit HttpSession(const QString &id, qint64 sessionTimeOut);


    ~HttpSession();
    /**
     * @brief Returns a session attribute given a name.
     * @warning: If the parameter is not found, nullptr is returned.
     */
    QObject *getAttribute(const QString &name) const;
    /**
     * @brief Returns a session attribute given a name.
     */
    QStringList getAttributeNames();
    /**
     * @brief getCreationTime
     */
    inline qint64 getCreationTime() const { return creationTime; }
    /**
     * @brief Returns the unique id
     */
    QString getId() const;
    /**
     * @brief Returns the time of the last session access.
     */
    inline qint64 getLastAccessedTime() const { return lastAccessedTime; }
    /**
     * @brief Make a valid session.
     */
    void validate();
    /**
     * @brief Make a invalid session.
     */
    inline void invalidate() { expired = 1; }
    /**
     * @brief Removes all the items that have the key key from the map.
     * Returns the number of items removed which is usually 1 but will be 0
     * if the key isn't in the map, or > 1 if insertMulti() has been used with the key.
     */
    inline int removeAttribute(const QString &name) { return attributes.remove(name); }
    /**
     * @brief This method add an attribute to the session.
     */
    inline void addAttribute(const QString &name, QObject *value) { attributes.insert(name, value); }
    /**
     * @brief getAutoClearAttributes
     */
    inline bool getAutoClearAttributes() const { return autoClearAttributes; }
    /**
     * @brief setAutoClearAttributes
     */
    inline void setAutoClearAttributes(bool value) { autoClearAttributes = value; }
    /**
     * @brief This method returns true if the session is expired otherwise returns false.
     */
    bool isExpired();
    /**
     * @brief Returns the session timeout.
     */
    inline qint64 getSessionTimeOut() const { return sessionTimeOut; }
    /**
     * @brief Sets the current session timeout.
     * If value is negative then it will be configured according to sessionExpirationTime of the CPPWeb.ini file.
     */
    void setSessionTimeOut(qint64 value);
};

CWF_END_NAMESPACE

#endif // HTTPSESSION_H

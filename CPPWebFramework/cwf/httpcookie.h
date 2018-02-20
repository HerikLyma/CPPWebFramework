/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef HTTPCOOKIE_H
#define HTTPCOOKIE_H

#include <QList>
#include <QDebug>
#include <QByteArray>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief This class represents a HTTP Cookie.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT HttpCookie
{
    QByteArray name;
    QByteArray value;
    QByteArray comment;
    QByteArray domain;
    QByteArray path;
    int maxAge  = 0;
    int version = 1;
    bool secure = false;
public:
    /**
     * @brief This is the cookie's default constructor.
     */
    HttpCookie() = default;
    /**
      Create a cookie from a string.
      @param source String as received in a HTTP Cookie2 header.
    */
    explicit HttpCookie(const QByteArray &source);
    /**
     * @brief This is an overloaded constructor that receives a cookie's name and value.
     * @param name  : This is a reference to a QByteArray. It will change the cookie's name.
     * @param value : This is a reference to a QByteArray. It will change the cookie's value.
     */
    HttpCookie(const QByteArray &name, const QByteArray &value);
    /** Convert this cookie to a string that may be used in a Set-Cookie header. */
    QByteArray toByteArray() const ;
    /**
     * @brief splitCSV
     * @param source
     * @return
     */
    static QList<QByteArray> splitCSV(const QByteArray &source);
    /**
     * @brief setName
     */
    inline void setName(const QByteArray &value) { name = value; }
    /**
     * @brief setValue
     */
    inline void setValue(const QByteArray &value) { this->value = value; }
    /**
     * @brief setComment
     */
    inline void setComment(const QByteArray &value) { comment = value; }
    /**
     * @brief setDomain     
     */
    inline void setDomain(const QByteArray &value) { domain = value; }
    /**
     * @brief setMaxAge
     */
    inline void setMaxAge(int value) { maxAge = value; }
    /**
     * @brief setPath
     */
    inline void setPath(const QByteArray &value) { path = value; }
    /**
     * @brief setSecure
     */
    inline void setSecure(bool value) { secure = value; }
    /**
     * @brief getName
     */
    inline QByteArray getName() const { return name; }
    /**
     * @brief getValue
     */
    inline QByteArray getValue() const { return value; }
    /**
     * @brief getComment
     */
    inline QByteArray getComment() const { return comment; }
    /**
     * @brief getDomain
     */
    inline QByteArray getDomain() const { return domain; }
    /**
     * @brief getMaxAge
     */
    inline int getMaxAge() const { return maxAge; }
    /**
     * @brief getPath
     */
    inline QByteArray getPath() const { return path; }
    /**
     * @brief getSecure
     */
    inline bool getSecure() const { return secure; }
    /**
     * @brief getVersion
     */
    inline int getVersion() const { return version; }
};

CWF_END_NAMESPACE

#endif // HTTPCOOKIE_H

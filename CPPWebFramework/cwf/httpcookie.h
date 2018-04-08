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
    inline void setName(const QByteArray &value) noexcept { name = value; }
    /**
     * @brief setValue
     */
    inline void setValue(const QByteArray &value) noexcept { this->value = value; }
    /**
     * @brief setComment
     */
    inline void setComment(const QByteArray &value) noexcept { comment = value; }
    /**
     * @brief setDomain     
     */
    inline void setDomain(const QByteArray &value) noexcept { domain = value; }
    /**
     * @brief setMaxAge
     */
    inline void setMaxAge(int value) noexcept { maxAge = value; }
    /**
     * @brief setPath
     */
    inline void setPath(const QByteArray &value) noexcept { path = value; }
    /**
     * @brief setSecure
     */
    inline void setSecure(bool value) noexcept { secure = value; }
    /**
     * @brief getName
     */
    inline QByteArray getName() const noexcept { return name; }
    /**
     * @brief getValue
     */
    inline QByteArray getValue() const noexcept { return value; }
    /**
     * @brief getComment
     */
    inline QByteArray getComment() const noexcept { return comment; }
    /**
     * @brief getDomain
     */
    inline QByteArray getDomain() const noexcept { return domain; }
    /**
     * @brief getMaxAge
     */
    inline int getMaxAge() const noexcept { return maxAge; }
    /**
     * @brief getPath
     */
    inline QByteArray getPath() const noexcept { return path; }
    /**
     * @brief getSecure
     */
    inline bool getSecure() const noexcept { return secure; }
    /**
     * @brief getVersion
     */
    inline int getVersion() const noexcept { return version; }
};

CWF_END_NAMESPACE

#endif // HTTPCOOKIE_H

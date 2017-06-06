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
     * @param name
     */
    void setName(const QByteArray &name);

    /**
     * @brief setValue
     * @param value
     */
    void setValue(const QByteArray &value);

    /**
     * @brief setComment
     * @param comment
     */
    void setComment(const QByteArray &comment);

    /**
     * @brief setDomain
     * @param domain
     */
    void setDomain(const QByteArray &domain);

    /**
     * @brief setMaxAge
     * @param maxAge
     */
    void setMaxAge(int maxAge);

    /**
     * @brief setPath
     * @param path
     */
    void setPath(const QByteArray &path);

    /**
     * @brief setSecure
     * @param secure
     */
    void setSecure(bool secure);

    /**
     * @brief getName
     * @return
     */
    QByteArray getName() const;

    /**
     * @brief getValue
     * @return
     */
    QByteArray getValue() const;

    /**
     * @brief getComment
     * @return
     */
    QByteArray getComment() const;

    /**
     * @brief getDomain
     * @return
     */
    QByteArray getDomain() const;

    /**
     * @brief getMaxAge
     * @return
     */
    int getMaxAge() const;

    /**
     * @brief getPath
     * @return
     */
    QByteArray getPath() const;

    /**
     * @brief getSecure
     * @return
     */
    bool getSecure() const;

    /**
     * @brief getVersion
     * @return
     */
    int getVersion() const;
};

CWF_END_NAMESPACE

#endif // HTTPCOOKIE_H

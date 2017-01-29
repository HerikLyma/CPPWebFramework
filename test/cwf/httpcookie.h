/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef HTTPCOOKIE_H
#define HTTPCOOKIE_H

#include <QByteArray>
#include <QList>

namespace CWF
{
    /**
     * @brief This class represents a HTTP Cookie.
     */
    class HttpCookie
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
          Split a string list into parts, where each part is delimited by semicolon.
          Semicolons within double quotes are skipped. Double quotes are removed.
        */
        static QList<QByteArray> splitCSV(const QByteArray &source);

        /** Set the name of this cookie */
        void setName(const QByteArray &name);

        /** Set the value of this cookie */
        void setValue(const QByteArray &value);

        /** Set the comment of this cookie */
        void setComment(const QByteArray &comment);

        /** Set the domain of this cookie */
        void setDomain(const QByteArray &domain);

        /** Set the maximum age of this cookie in seconds. 0=discard immediately */
        void setMaxAge(int maxAge);

        /** Set the path for that the cookie will be sent, default="/" which means the whole domain */
        void setPath(const QByteArray &path);

        /** Set secure mode, so that the cokkie will only be sent on secure connections */
        void setSecure(bool secure);

        /** Get the name of this cookie */
        QByteArray getName() const;

        /** Get the value of this cookie */
        QByteArray getValue() const;

        /** Get the comment of this cookie */
        QByteArray getComment() const;

        /** Get the domain of this cookie */
        QByteArray getDomain() const;

        /** Set the maximum age of this cookie in seconds. */
        int getMaxAge() const;

        /** Set the path of this cookie */
        QByteArray getPath() const;

        /** Get the secure flag of this cookie */
        bool getSecure() const;

        /** Returns always 1 */
        int getVersion() const;
    };
}
#endif // HTTPCOOKIE_H

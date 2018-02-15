/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QMap>
#include <QVector>
#include <QByteArray>
#include "httpcookie.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The class parses a HTTP message.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT HttpParser
{
    friend class HttpReadRequest;
    qint64     contentLenght = 0;
    QByteArray contentType;
    QByteArray httpVersion;
    QByteArray method;
    QByteArray body;
    QByteArray sessionId;
    QByteArray url;
    QMultiMap<QByteArray, QByteArray> parameters;
    QMultiMap<QByteArray, QByteArray> headerField;
    QMultiMap<QByteArray, QByteArray> files;
    QVector<HttpCookie> cookies;
    bool    valid     = false;
    bool    multiPart = false;
    bool    readFile  = false;
    bool    extractHeaderAndBody(QByteArray &httpMessage);
    void    doParse(QByteArray &httpMessage);
    void    doParseHttpHeader(QByteArray &httpMessage);
    void    doParseUrl();
    void    doParseBody();
    void    doParseFiles();
    void    extractCookies();
public:
    /**
     * @brief This constructor receives a HTTP message and parses it.
     * @param QByteArray &httpMessage : HTTP message.
     */
    explicit HttpParser(QByteArray &httpMessage);
    /**
     * @brief Returns the content lenght.
     * @return qint64 : Content length.
     */
    qint64 getContentLenght() const;
    /**
     * @brief Returns the content type.
     * @return QByteArray : Content type.
     */
    QByteArray getContentType() const;
    /**
     * @brief Returns the HTTP version.
     * @return QByteArray : HTTP version.
     */
    QByteArray getHttpVersion() const;
    /**
     * @brief Returns HTTP method.
     * @return QByteArray : HTTP method.
     */
    QByteArray getMethod() const;
    /**
     * @brief Returns HTTP body message.
     * @return QByteArray : HTTP body message.
     */
    QByteArray getBody() const;
    /**
     * @brief Returns session id.
     * @return QByteArray : session id.
     */
    QByteArray getSessionId() const;
    /**
     * @brief Returns the url.
     * @return QByteArray : url.
     */
    QByteArray getUrl() const;
    /**
     * @brief Returns a specific parameter given a name.
     * If the parameter name does not exists, the function returns defaultValue.
     * If no defaultValue is specified, the function returns a default-constructed value.
     * If there are multiple parameters with a name, the value of the most recently inserted one is returned.
     * @param const QByteArray &name : Parameter name.
     * @return QByteArray : Parameter value.
     */
    QByteArray getParameter(const QByteArray &name) const;
    /**
     * @brief Returns all parameters with a specific name.
     * @param const QByteArray &name : Parameter name.
     * @return QByteArrayList : Parameters list.
     */
    QByteArrayList getParameters(const QByteArray &name) const;
    /**
     * @brief Returns all parameters.
     * @return QMap<QByteArray, QByteArray> : Parameters name and value.
     */
    QMultiMap<QByteArray, QByteArray> getParameters() const;
    /**
     * @brief Returns all uploaded files.
     * @return QMultiMap<QByteArray, QByteArray> : Files name and content.
     */
    QMultiMap<QByteArray, QByteArray> getUploadedFiles() const;
    /**
     * @brief Returns all cookies.
     * @return QVector<HttpCookie> : Cookies.
     */
    QVector<HttpCookie> getCookies() const;
    /**
     * @brief Returns all header fields given a specific name.
     * @param const QByteArray &headerField : Header field name.
     * @return QByteArrayList : Header fields.
     */
    QByteArrayList getHeaderFields(const QByteArray &name) const;
    /**
     * @brief Returns a specific header field given a name.
     * If the header field name does not exists, the function returns defaultValue.
     * If no defaultValue is specified, the function returns a default-constructed value.
     * If there are multiple header field with a name, the value of the most recently inserted one is returned.
     * @param const QByteArray &name : Parameter name.
     * @return QByteArray : Parameter value.
     */
    QByteArray getHeaderField(const QByteArray &name) const;
    /**
     * @brief Returns true if HTTP is valid, else it returns false.
     * @return bool : HTTP message valid.
     */
    bool isValid() const;
    /**
     * @brief Returns the multi part.
     * @return bool : Multi part.
     */
    bool isMultiPart() const;
    /**
     * @brief Returns true if all message was read.
     * @return bool : Read file.
     */
    bool getReadFile() const;
};

CWF_END_NAMESPACE

#endif // HTTPPARSER_H

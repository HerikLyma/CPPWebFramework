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
#include <QNetworkCookie>
#include "urlencoder.h"
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
    QVector<QNetworkCookie> cookies;
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
    explicit HttpParser(QByteArray &httpMessage) { doParse(httpMessage); }
    /**
     * @brief Returns the content lenght.
     * @return qint64 : Content length.
     */
    inline qint64 getContentLenght() const noexcept { return contentLenght; }
    /**
     * @brief Returns the content type.
     * @return QByteArray : Content type.
     */
    inline QByteArray getContentType() const noexcept { return contentType; }
    /**
     * @brief Returns the HTTP version.
     * @return QByteArray : HTTP version.
     */
    inline QByteArray getHttpVersion() const noexcept { return httpVersion; }
    /**
     * @brief Returns HTTP method.
     * @return QByteArray : HTTP method.
     */
    inline QByteArray getMethod() const noexcept { return method; }
    /**
     * @brief Returns HTTP body message.
     * @return QByteArray : HTTP body message.
     */
    inline QByteArray getBody() const noexcept { return body; }
    /**
     * @brief Returns session id.
     * @return QByteArray : session id.
     */
    inline QByteArray getSessionId() const noexcept { return sessionId; }
    /**
     * @brief Returns the url.
     * @return QByteArray : url.
     */
    inline QByteArray getUrl() const noexcept { return url; }
    /**
     * @brief Returns a specific parameter given a name.
     * If the parameter name does not exists, the function returns defaultValue.
     * If no defaultValue is specified, the function returns a default-constructed value.
     * If there are multiple parameters with a name, the value of the most recently inserted one is returned.
     * @param const QByteArray &name : Parameter name.
     * @return QByteArray : Parameter value.
     */
    inline QByteArray getParameter(const QByteArray &name, bool urlDecode = true, bool replacePlusForSpace = true) const noexcept
    {
        return urlDecode ? URLEncoder::paramDecode(parameters.value(name), replacePlusForSpace).toUtf8() : parameters.value(name);
    }
    /**
     * @brief Returns all parameters with a specific name.
     * @param const QByteArray &name : Parameter name.
     * @return QByteArrayList : Parameters list.
     */
    inline QByteArrayList getParameters(const QByteArray &name) const noexcept { return parameters.values(name); }
    /**
     * @brief Returns all parameters.
     * @return QMap<QByteArray, QByteArray> : Parameters name and value.
     */
    inline QMultiMap<QByteArray, QByteArray> getParameters() const noexcept { return parameters; }
    /**
     * @brief Returns all uploaded files.
     * @return QMultiMap<QByteArray, QByteArray> : Files name and content.
     */
    inline QMultiMap<QByteArray, QByteArray> getUploadedFiles() const noexcept { return files; }
    /**
     * @brief Returns all cookies.
     * @return QVector<QNetworkCookie> : Cookies.
     */
    inline QVector<QNetworkCookie> getCookies() const noexcept { return cookies; }
    /**
     * @brief Returns all header fields given a specific name.
     * @param const QByteArray &headerField : Header field name.
     * @return QByteArrayList : Header fields.
     */
    inline QByteArrayList getHeaderFields(const QByteArray &name) const noexcept { return headerField.values(name); }
    /**
     * @brief Returns a specific header field given a name.
     * If the header field name does not exists, the function returns defaultValue.
     * If no defaultValue is specified, the function returns a default-constructed value.
     * If there are multiple header field with a name, the value of the most recently inserted one is returned.
     * @param const QByteArray &name : Parameter name.
     * @return QByteArray : Parameter value.
     */
    inline QByteArray getHeaderField(const QByteArray &name) const noexcept { return headerField.value(name); }
    /**
     * @brief Returns true if HTTP is valid, else it returns false.
     * @return bool : HTTP message valid.
     */
    inline bool isValid() const noexcept { return valid; }
    /**
     * @brief Returns the multi part.
     * @return bool : Multi part.
     */
    inline bool isMultiPart() const noexcept { return multiPart; }
    /**
     * @brief Returns true if all message was read.
     * @return bool : Read file.
     */
    inline bool getReadFile() const noexcept { return readFile; }
};

CWF_END_NAMESPACE

#endif // HTTPPARSER_H

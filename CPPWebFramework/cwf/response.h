/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef RESPONSE_H
#define RESPONSE_H

#include <QFile>
#include <QTcpSocket>
#include <QTextStream>
#include <QJsonDocument>
#include <QNetworkCookie>
#include "constants.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE

class Configuration;
/**
 * @brief The Response class is responsable to response a Http request.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT Response
{
    QTcpSocket     &socket;
    const Configuration &configuration;
    int            statusCode = Response::SC_OK;
    QByteArray     content;
    QByteArray     statusText = HTTP::OK;
    QMap<QByteArray, QByteArray> headers;
    QVector<QNetworkCookie> cookies;
public:
    Response(QTcpSocket &socket, const Configuration &configuration);

    ~Response() noexcept {}

    void write(const QJsonObject &json, bool writeContentType = true);

    void write(const QJsonArray &array, bool writeContentType = true);

    void write(QByteArray &&data);

    void write(const QByteArray &data, bool flush = true);

    void sendError(int sc, const QByteArray &msg);

    void flushBuffer();

    inline int getBufferSize() const noexcept { return content.size(); }

    inline void addHeader(const QByteArray &name, const QByteArray &value) noexcept { headers.insert(name, value); }

    inline void addCookie(const QNetworkCookie &cookie) noexcept { cookies.push_back(cookie); }

    void setStatus(int statusCode, const QByteArray &description);

    void sendRedirect(const QByteArray &url);

    static const int SC_CONTINUE;

    static const int SC_SWITCHING_PROTOCOLS;

    static const int SC_OK;

    static const int SC_CREATED;

    static const int SC_ACCEPTED;

    static const int SC_NON_AUTHORITATIVE_INFORMATION;

    static const int SC_NO_CONTENT;

    static const int SC_RESET_CONTENT;

    static const int SC_PARTIAL_CONTENT;

    static const int SC_MULTIPLE_CHOICES;

    static const int SC_MOVED_PERMANENTLY;

    static const int SC_MOVED_TEMPORARILY;

    static const int SC_FOUND;

    static const int SC_SEE_OTHER;

    static const int SC_NOT_MODIFIED;

    static const int SC_USE_PROXY;

    static const int SC_TEMPORARY_REDIRECT;

    static const int SC_BAD_REQUEST;

    static const int SC_UNAUTHORIZED;

    static const int SC_PAYMENT_REQUIRED;

    static const int SC_FORBIDDEN;

    static const int SC_NOT_FOUND;

    static const int SC_METHOD_NOT_ALLOWED;

    static const int SC_NOT_ACCEPTABLE;

    static const int SC_PROXY_AUTHENTICATION_REQUIRED;

    static const int SC_REQUEST_TIMEOUT;

    static const int SC_CONFLICT;

    static const int SC_GONE;

    static const int SC_LENGTH_REQUIRED;

    static const int SC_PRECONDITION_FAILED;

    static const int SC_REQUEST_ENTITY_TOO_LARGE;

    static const int SC_REQUEST_URI_TOO_LONG;

    static const int SC_UNSUPPORTED_MEDIA_TYPE;

    static const int SC_REQUESTED_RANGE_NOT_SATISFIABLE;

    static const int SC_EXPECTATION_FAILED;

    static const int SC_INTERNAL_SERVER_ERROR;

    static const int SC_NOT_IMPLEMENTED;

    static const int SC_BAD_GATEWAY;

    static const int SC_SERVICE_UNAVAILABLE;

    static const int SC_GATEWAY_TIMEOUT;

    static const int SC_HTTP_VERSION_NOT_SUPPORTED;
};

CWF_END_NAMESPACE

#endif // RESPONSE_H

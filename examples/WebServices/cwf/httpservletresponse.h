/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef HTTPSERVLETRESPONSE_H
#define HTTPSERVLETRESPONSE_H

#include "httpcookie.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QFile>
#include <QThread>

namespace CWF
{
    /**
     * @brief The HttpServletResponse class is responsable to response a Http request.
     */
    class HttpServletResponse
    {
        QTcpSocket     *socket;

        int            statusCode;

        QByteArray     content;

        QByteArray     statusText;

        QString        httpStatus;

        QMap<QByteArray,QByteArray> headers;

        QVector<HttpCookie> cookies;
    public:
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

        explicit HttpServletResponse(QTcpSocket &socket);

        virtual ~HttpServletResponse();

        void write(const QByteArray &data, bool flush = true);

        void writeHeaders();

        void writeToSocket(const QByteArray &data);

        void sendError(int sc, const QByteArray &msg);

        void flushBuffer();

        int getBufferSize() const;

        void addHeader(const QByteArray &name, const QByteArray &value);

        void addCookie(const HttpCookie &cookie);

        void setStatus(const int &statusCode, const QByteArray &description);

        QTcpSocket &getSocket() const;

        void sendRedirect(const QByteArray &url);
    };
}

#endif // HTTPSERVLETRESPONSE_H

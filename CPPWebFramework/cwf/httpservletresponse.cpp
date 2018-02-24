/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "httpservletresponse.h"
#include "configuration.h"
#include "constants.h"
#include <QDateTime>

CWF_BEGIN_NAMESPACE

HttpServletResponse::HttpServletResponse(QTcpSocket &socket, const Configuration &configuration) : socket(&socket),
                                                                                                   configuration(configuration)
{
    statusCode       = HttpServletResponse::SC_OK;
    statusText       = HTTP::OK;
}

void HttpServletResponse::flushBuffer()
{
    const int max = 32768;
    if(!content.isEmpty())
    {
        bool biggerThanLimit = content.size() > max;
        headers.insert(HTTP::CONTENT_LENGTH, QByteArray::number(content.size()));
        headers.insert(HTTP::SERVER, HTTP::SERVER_VERSION);
        headers.insert(HTTP::DATA, QByteArray(std::move(QDateTime::currentDateTime().toString("ddd, dd MMM yyyy hh:mm:ss").toLatin1() + " GMT")));

        if(!biggerThanLimit)
        {
            writeHeaders();
            writeToSocket(content);
        }
        else
        {
            headers.insert(HTTP::TRANSFER_ENCODING, HTTP::CHUNKED);
            writeHeaders();
            int total = (content.size() / max) + 1, last = 0;

            QVector<QByteArray> vetor;
            for(int i = 0; i < total; ++i)
            {
                vetor.push_back(std::move(content.mid(last, max)));
                last += max;
            }

            for(int i = 0; i < vetor.size(); ++i)
            {
                QByteArray data(std::move(vetor[i]));
                if(!data.isEmpty())
                {
                    QByteArray buffer(std::move(QByteArray::number(data.size(), 16)));
                    buffer.append(HTTP::END_LINE);
                    writeToSocket(buffer);
                    writeToSocket(data);
                    writeToSocket(HTTP::END_LINE);
                }
            }
            writeToSocket(HTTP::END_OF_MENSAGE_WITH_ZERO);
        }
        socket->disconnectFromHost();
        content.clear();
    }
}

void HttpServletResponse::sendError(int sc, const QByteArray &msg)
{
    writeHeaders();
    writeToSocket("<html><body><h1>" + QByteArray::number(sc) + " " + msg + "</h1></body></html>");
}

void HttpServletResponse::write(const QJsonObject &json, bool writeContentType)
{
    if(writeContentType)
        addHeader(CWF::HTTP::CONTENT_TYPE, CWF::HTTP::APPLICATION_JSON);
    content = std::move(QJsonDocument(json).toJson());
    flushBuffer();
}

void HttpServletResponse::write(const QJsonArray &array, bool writeContentType)
{
    if(writeContentType)
        addHeader(CWF::HTTP::CONTENT_TYPE, CWF::HTTP::APPLICATION_JSON);
    content = std::move(QJsonDocument(array).toJson());
    flushBuffer();
}

void HttpServletResponse::write(QByteArray &&data)
{
    content = std::move(data);
    flushBuffer();
}

void HttpServletResponse::write(const QByteArray &data, bool flush)
{
    content += data;
    if(flush)
        flushBuffer();
}

void HttpServletResponse::setStatus(const int &statusCode, const QByteArray &description)
{
    this->statusCode = statusCode;
    statusText       = description;
}

void HttpServletResponse::writeToSocket(const QByteArray &data)
{
    socket->moveToThread(QThread::currentThread());
    if(socket->ConnectingState > 0 && data.size() > 0)
    {
        socket->write(data, data.size());
        socket->flush();
        //qDebug() << data;
        if(socket->ConnectingState > 0)
        {            
            int timeOut = configuration.getTimeOut();
            socket->waitForBytesWritten(timeOut);
        }
    }
}

void HttpServletResponse::writeHeaders()
{
    QByteArray buffer;

    buffer.append("HTTP/1.1 ");
    buffer.append(QByteArray::number(statusCode));
    buffer.append(' ');
    buffer.append(statusText);
    buffer.append(HTTP::END_LINE);

    if(!headers.contains(HTTP::CONTENT_TYPE))
    {
        headers.insert(HTTP::CONTENT_TYPE, HTTP::TEXT_HTML_UTF8);
    }

    QList<QByteArray> headersList(std::move(headers.keys()));

    for(QByteArray &name : headersList)
    {
        buffer.append(name);
        buffer.append(": ");
        buffer.append(headers.value(name));
        buffer.append(HTTP::END_LINE);
    }
    for(HttpCookie &cookie : cookies)
    {
        buffer.append("Set-Cookie: ");
        buffer.append(cookie.toByteArray());
        buffer.append(HTTP::END_LINE);
    }
    buffer.append(HTTP::END_LINE);
    writeToSocket(buffer);
}

void HttpServletResponse::sendRedirect(const QByteArray &url)
{
    setStatus(HttpServletResponse::SC_SEE_OTHER, HTTP::SEE_OTHER);
    addHeader(HTTP::LOCATION, url);
    write(HTTP::REDIRECT, true);
}

const int HttpServletResponse::SC_CONTINUE = 100;

const int HttpServletResponse::SC_SWITCHING_PROTOCOLS = 101;

const int HttpServletResponse::SC_OK = 200;

const int HttpServletResponse::SC_CREATED = 201;

const int HttpServletResponse::SC_ACCEPTED = 202;

const int HttpServletResponse::SC_NON_AUTHORITATIVE_INFORMATION = 203;

const int HttpServletResponse::SC_NO_CONTENT = 204;

const int HttpServletResponse::SC_RESET_CONTENT = 205;

const int HttpServletResponse::SC_PARTIAL_CONTENT = 206;

const int HttpServletResponse::SC_MULTIPLE_CHOICES = 300;

const int HttpServletResponse::SC_MOVED_PERMANENTLY = 301;

const int HttpServletResponse::SC_MOVED_TEMPORARILY = 302;

const int HttpServletResponse::SC_FOUND = 302;

const int HttpServletResponse::SC_SEE_OTHER = 303;

const int HttpServletResponse::SC_NOT_MODIFIED = 304;

const int HttpServletResponse::SC_USE_PROXY = 305;

const int HttpServletResponse::SC_TEMPORARY_REDIRECT = 307;

const int HttpServletResponse::SC_BAD_REQUEST = 400;

const int HttpServletResponse::SC_UNAUTHORIZED = 401;

const int HttpServletResponse::SC_PAYMENT_REQUIRED = 402;

const int HttpServletResponse::SC_FORBIDDEN = 403;

const int HttpServletResponse::SC_NOT_FOUND = 404;

const int HttpServletResponse::SC_METHOD_NOT_ALLOWED = 405;

const int HttpServletResponse::SC_NOT_ACCEPTABLE = 406;

const int HttpServletResponse::SC_PROXY_AUTHENTICATION_REQUIRED = 407;

const int HttpServletResponse::SC_REQUEST_TIMEOUT = 408;

const int HttpServletResponse::SC_CONFLICT = 409;

const int HttpServletResponse::SC_GONE = 410;

const int HttpServletResponse::SC_LENGTH_REQUIRED = 411;

const int HttpServletResponse::SC_PRECONDITION_FAILED = 412;

const int HttpServletResponse::SC_REQUEST_ENTITY_TOO_LARGE = 413;

const int HttpServletResponse::SC_REQUEST_URI_TOO_LONG = 414;

const int HttpServletResponse::SC_UNSUPPORTED_MEDIA_TYPE = 415;

const int HttpServletResponse::SC_REQUESTED_RANGE_NOT_SATISFIABLE = 416;

const int HttpServletResponse::SC_EXPECTATION_FAILED = 417;

const int HttpServletResponse::SC_INTERNAL_SERVER_ERROR = 500;

const int HttpServletResponse::SC_NOT_IMPLEMENTED = 501;

const int HttpServletResponse::SC_BAD_GATEWAY = 502;

const int HttpServletResponse::SC_SERVICE_UNAVAILABLE = 503;

const int HttpServletResponse::SC_GATEWAY_TIMEOUT = 504;

const int HttpServletResponse::SC_HTTP_VERSION_NOT_SUPPORTED = 505;

CWF_END_NAMESPACE

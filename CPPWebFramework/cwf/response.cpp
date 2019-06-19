/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "response.h"
#include "configuration.h"
#include <QDateTime>

CWF_BEGIN_NAMESPACE

Response::Response(QTcpSocket &socket, const Configuration &configuration) : socket(socket),
                                                                             configuration(configuration)

{
}

void sendBytes(QTcpSocket &socket, const QByteArray &text, int timeOut)
{
    if(socket.ConnectingState > 0 && text.size() > 0)
    {
        socket.write(text, text.size());
        socket.flush();

        if(socket.ConnectingState > 0)
        {
            socket.waitForBytesWritten(timeOut);
        }
    }
}

void buildHeadersString(QByteArray &temp, const QMap<QByteArray, QByteArray> &headers)
{
    QList<QByteArray> headersList(headers.keys());

    for(const auto &i : headersList)
    {
        temp.push_back(i);
        temp.push_back(HTTP::SEPARATOR);
        temp.push_back(headers.value(i));
        temp.push_back(HTTP::END_LINE);
    }
}

void buildCookiesString(QByteArray &temp, const QVector<QNetworkCookie> &cookies)
{
    for(const auto &i : cookies)
    {
        temp.push_back(HTTP::SET_COOKIE);
        temp.push_back(i.toRawForm());
        temp.push_back(HTTP::END_LINE);
    }
}

void sendHeaders(int statusCode,
                 int timeOut,
                 const QByteArray &statusText,
                 QMap<QByteArray, QByteArray> &headers,
                 QVector<QNetworkCookie> &cookies,
                 QTcpSocket &socket)
{
    QByteArray temp(HTTP::HTTP_1_1);
    temp.reserve(100);
    temp.push_back(QByteArray::number(statusCode));
    temp.push_back(' ');
    temp.push_back(statusText);
    temp.push_back(HTTP::END_LINE);

    if(!headers.contains(HTTP::CONTENT_TYPE))
    {
        headers.insert(HTTP::CONTENT_TYPE, HTTP::TEXT_HTML_UTF8);
    }

    buildHeadersString(temp, headers);
    buildCookiesString(temp, cookies);
    temp.push_back(HTTP::END_LINE);
    sendBytes(socket, temp, timeOut);
}

void Response::flushBuffer()
{
    const int max = 32768;
    if(!content.isEmpty())
    {
        int timeOut = configuration.getTimeOut();
        bool biggerThanLimit = content.size() > max;
        headers.insert(HTTP::CONTENT_LENGTH, QByteArray::number(content.size()));
        headers.insert(HTTP::SERVER, HTTP::SERVER_VERSION);
        headers.insert(HTTP::DATA, QByteArray(QDateTime::currentDateTime().toString("ddd, dd MMM yyyy hh:mm:ss").toLatin1() + " GMT"));

        if(!biggerThanLimit)
        {
            sendHeaders(statusCode, timeOut, statusText, headers, cookies, socket);
            sendBytes(socket, content, timeOut);
        }
        else
        {
            headers.insert(HTTP::TRANSFER_ENCODING, HTTP::CHUNKED);
            sendHeaders(statusCode, timeOut, statusText, headers, cookies, socket);
            int total = (content.size() / max) + 1, last = 0;

            QVector<QByteArray> vetor;
            for(int i = 0; i < total; ++i)
            {
                vetor.push_back(content.mid(last, max));
                last += max;
            }

            for(auto &i : vetor)
            {
                QByteArray data(std::move(i));
                if(!data.isEmpty())
                {
                    sendBytes(socket, (QByteArray::number(data.size(), 16) + HTTP::END_LINE), timeOut);
                    sendBytes(socket, data, timeOut);
                    sendBytes(socket, HTTP::END_LINE, timeOut);
                }
            }
            sendBytes(socket, HTTP::END_OF_MESSAGE_WITH_ZERO, timeOut);
        }
        socket.disconnectFromHost();
        content.clear();
    }
}

void Response::sendError(int sc, const QByteArray &msg)
{
    int timeOut = configuration.getTimeOut();
    sendHeaders(statusCode, timeOut, statusText, headers, cookies, socket);
    sendBytes(socket, "<html><body><h1>" + QByteArray::number(sc) + " " + msg + "</h1></body></html>", timeOut);
}

void Response::write(const QJsonObject &json, bool writeContentType)
{
    if(writeContentType)
        addHeader(CWF::HTTP::CONTENT_TYPE, CWF::HTTP::APPLICATION_JSON);
    content = QJsonDocument(json).toJson();
    flushBuffer();
}

void Response::write(const QJsonArray &array, bool writeContentType)
{
    if(writeContentType)
        addHeader(CWF::HTTP::CONTENT_TYPE, CWF::HTTP::APPLICATION_JSON);
    content = QJsonDocument(array).toJson();
    flushBuffer();
}

void Response::write(QByteArray &&data)
{
    content = std::move(data);
    flushBuffer();
}

void Response::write(const QByteArray &data, bool flush)
{
    content += data;
    if(flush)
        flushBuffer();
}

void Response::setStatus(int statusCode, const QByteArray &description)
{
    this->statusCode = statusCode;
    statusText       = description;
}

void Response::sendRedirect(const QByteArray &url)
{
    setStatus(Response::SC_SEE_OTHER, HTTP::SEE_OTHER);
    addHeader(HTTP::LOCATION, url);
    write(HTTP::REDIRECT, true);
}

const int Response::SC_CONTINUE = 100;

const int Response::SC_SWITCHING_PROTOCOLS = 101;

const int Response::SC_OK = 200;

const int Response::SC_CREATED = 201;

const int Response::SC_ACCEPTED = 202;

const int Response::SC_NON_AUTHORITATIVE_INFORMATION = 203;

const int Response::SC_NO_CONTENT = 204;

const int Response::SC_RESET_CONTENT = 205;

const int Response::SC_PARTIAL_CONTENT = 206;

const int Response::SC_MULTIPLE_CHOICES = 300;

const int Response::SC_MOVED_PERMANENTLY = 301;

const int Response::SC_MOVED_TEMPORARILY = 302;

const int Response::SC_FOUND = 302;

const int Response::SC_SEE_OTHER = 303;

const int Response::SC_NOT_MODIFIED = 304;

const int Response::SC_USE_PROXY = 305;

const int Response::SC_TEMPORARY_REDIRECT = 307;

const int Response::SC_BAD_REQUEST = 400;

const int Response::SC_UNAUTHORIZED = 401;

const int Response::SC_PAYMENT_REQUIRED = 402;

const int Response::SC_FORBIDDEN = 403;

const int Response::SC_NOT_FOUND = 404;

const int Response::SC_METHOD_NOT_ALLOWED = 405;

const int Response::SC_NOT_ACCEPTABLE = 406;

const int Response::SC_PROXY_AUTHENTICATION_REQUIRED = 407;

const int Response::SC_REQUEST_TIMEOUT = 408;

const int Response::SC_CONFLICT = 409;

const int Response::SC_GONE = 410;

const int Response::SC_LENGTH_REQUIRED = 411;

const int Response::SC_PRECONDITION_FAILED = 412;

const int Response::SC_REQUEST_ENTITY_TOO_LARGE = 413;

const int Response::SC_REQUEST_URI_TOO_LONG = 414;

const int Response::SC_UNSUPPORTED_MEDIA_TYPE = 415;

const int Response::SC_REQUESTED_RANGE_NOT_SATISFIABLE = 416;

const int Response::SC_EXPECTATION_FAILED = 417;

const int Response::SC_INTERNAL_SERVER_ERROR = 500;

const int Response::SC_NOT_IMPLEMENTED = 501;

const int Response::SC_BAD_GATEWAY = 502;

const int Response::SC_SERVICE_UNAVAILABLE = 503;

const int Response::SC_GATEWAY_TIMEOUT = 504;

const int Response::SC_HTTP_VERSION_NOT_SUPPORTED = 505;

CWF_END_NAMESPACE

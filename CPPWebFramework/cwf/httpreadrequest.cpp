/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "httpreadrequest.h"
#include "configuration.h"
#include "constants.h"

CWF_BEGIN_NAMESPACE

HttpReadRequest::HttpReadRequest(qintptr socketDescriptor,
                                 QMapThreadSafety<QString, Controller *> &urlController,
                                 QMapThreadSafety<QString, Session *> &sessions,
                                 const Configuration &configuration,
                                 QSslConfiguration *ssl,
                                 Filter *filter) :
    socketDescriptor(socketDescriptor),
    urlController(urlController),
    sessions(sessions),
    configuration(configuration),
    ssl(ssl),
    filter(filter)
{
}

HttpReadRequest::~HttpReadRequest()
{
    delete socket;
}

bool HttpReadRequest::buildSslSocket()
{
#ifndef QT_NO_SSL
    if(ssl)
    {
        auto *sslSocket = new QSslSocket;
        socket = sslSocket;
        sslSocket->setSslConfiguration(*ssl);
        sslSocket->setSocketDescriptor(socketDescriptor);
        sslSocket->startServerEncryption();
        return true;
    }
#endif
    return false;
}

void HttpReadRequest::buildSocket()
{
    if(!buildSslSocket())
    {
        socket = new QTcpSocket;
        socket->setSocketDescriptor(socketDescriptor);
    }
}

void HttpReadRequest::run()
{
    buildSocket();
    maxUploadFile = configuration.getMaxUploadFile();
    socket->setReadBufferSize(maxUploadFile);
    if(socket->ConnectedState > 0)
    {
        if(socket->waitForReadyRead())
        {
            QByteArray req;
            try {
                req = socket->readAll();
            } catch (const std::bad_alloc & e) {
                qDebug() << e.what() << "\n";
            }


            HttpParser parser(req);
            if(parser.valid)
            {
                QString url = parser.url;
                Request request(*socket, sessions, configuration);
                Response response(*socket, configuration);
                request.httpParser = &parser;
                request.response   = &response;

                if(parser.contentLenght > parser.body.size())
                {
                    if(!readBody(parser, request, response))
                    {
                        return;
                    }
                }
                Controller *controller = urlController.value(url, nullptr);
                if(!controller)
                {
                    for(QMapThreadSafety<QString, Controller *>::iterator it = urlController.begin(); it != urlController.end(); ++it)
                    {
                        const QString &key = it.key();
                        if(key.endsWith('*'))
                        {
                            QString trueUrl(key.mid(0, key.size() - 1));
                            if(url.startsWith(trueUrl))
                            {
                                url = trueUrl + "*";
                                controller = it.value();
                                break;
                            }
                        }
                    }
                }
                FilterChain chain(controller, configuration);
                try
                {
                    if(filter)
                    {
                        filter->doFilter(request, response, chain);
                    }
                    else
                    {
                        chain.doFilter(request, response);
                    }
                }
                catch(std::exception &e)
                {
                    qDebug() << e.what();
                }
                catch(...)
                {
                    qDebug() << "An unknown exception has occurred\n\n";
                }
            }
        }
    }
}


bool HttpReadRequest::readBody(HttpParser &parser, Request &request, Response &response)
{
    qint64 contentLength = parser.contentLenght;
    QByteArray content(std::move(parser.body));
    int maximumTime = configuration.getTimeOut() / 2;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    while(true)
    {
        if(socket->waitForReadyRead(10))
        {
            if (content.size() > maxUploadFile) {
                socket->readAll();// what if the  internal buffer throws a
            } else {
                try {
                    content += socket->readAll();
                } catch (const std::bad_alloc &e) {
                    qDebug() << e.what() << "\n";
                    break;
                }

            }
        }

        int spendTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();

        if(content.size() > contentLength)
        {
            content.remove(contentLength, content.size());
            break;
        }
        if(content.size() == contentLength)
        {
            break;
        }
        if(spendTime >= maximumTime)
        {
            break;
        }
    }

    if(content.size() > maxUploadFile)
    {
        request.getRequestDispatcher(STATUS::STATUS_403).forward(request, response);
        return false;
    }

    parser.body = std::move(content);

    if(parser.contentType.contains(HTTP::APPLICATION_WWW_FORM_URLENCODED))
    {
        parser.doParseBody();
    }
    else if(parser.multiPart)
    {
        parser.doParseFiles();
    }

    return true;
}

CWF_END_NAMESPACE

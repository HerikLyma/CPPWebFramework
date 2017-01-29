/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "httpreadrequest.h"
#include "configuration.h"

namespace CWF
{
    extern Configuration configuration;

    HttpReadRequest::HttpReadRequest(qintptr socketDescriptor,
                                     QMapThreadSafety<QString, HttpServlet *> &urlServlet,
                                     QMapThreadSafety<QString, HttpSession *> &sessions,
                                     QSslConfiguration *sslConfiguration,
                                     Filter *filter) :
                                                        socketDescriptor(socketDescriptor),
                                                        urlServlet(urlServlet),                                                        
                                                        sessions(sessions),
                                                        sslConfiguration(sslConfiguration),
                                                        filter(filter)
    {
    }

    HttpReadRequest::~HttpReadRequest()
    {
        if(socket)
        {
            delete socket;
        }
    }

    void HttpReadRequest::run()
    {
        createSocket();
        socket->setSocketDescriptor(socketDescriptor);

#ifndef QT_NO_OPENSSL
        if (sslConfiguration)
        {
            ((QSslSocket*)socket)->startServerEncryption();
        }
#endif
        socket->thread()->setPriority(QThread::TimeCriticalPriority);
        mutex.lock();
        maxUploadFile = configuration.maxUploadFile;
        mutex.unlock();
        socket->setReadBufferSize(maxUploadFile);
        if(socket->ConnectedState)
        {
            if(socket->waitForReadyRead())
            {
                QByteArray req(std::move(socket->readAll()));
                //qDebug() << req;

                HttpParser parser(req);
                if(parser.valid)
                {                    
                    QString               url      = parser.url;
                    HttpServlet          *servlet  = nullptr;
                    HttpSession          *session  = nullptr;
                    mutex.lock();
                    HttpServletRequest   request(*socket, configuration.path, configuration.suffix);                    
                    mutex.unlock();
                    HttpServletResponse  response(*socket);
                    request.httpParser = &parser;


                    if(parser.contentLenght > parser.body.size())
                    {
                        if(!readBody(parser, request, response))
                        {
                            return;
                        }
                    }

                    bool contains = urlServlet.contains(url);
                    if(!contains)
                    {
                        for(QMapThreadSafety<QString, HttpServlet *>::iterator it = urlServlet.begin(); it != urlServlet.end(); ++it)
                        {
                            const QString &key = it.key();
                            if(key.endsWith('*'))
                            {
                                QString trueUrl(std::move(key.mid(0, key.size() - 1)));
                                if(url.startsWith(trueUrl))
                                {
                                    url = trueUrl + "*";
                                    contains = true;
                                    break;
                                }
                            }
                        }
                    }

                    if(contains)
                    {
                        servlet = urlServlet[url];
                        QByteArray sessionId(parser.sessionId);
                        bool dontHasSessionId = sessionId.isEmpty();                        
                        qint64 currentTimeInt = QDateTime::currentMSecsSinceEpoch();
                        if(sessions.contains(sessionId))
                        {
                            session = sessions[sessionId];
                            mutex.lock();
                            if(!session->expired)
                            {
                                session->expired = (currentTimeInt >= session->sessionExpirationTime);
                                if(!session->expired)
                                    session->sessionExpirationTime = (currentTimeInt + configuration.sessionExpirationTime);                                    
                            }
                            mutex.unlock();
                        }
                        else
                        {
                            if(dontHasSessionId)
                            {
                                sessionId = SessionIdGenerator(parser).getSessionID();
                                response.addCookie(HttpCookie("sessionId", sessionId));
                            }

                            session = new HttpSession(sessionId);
                            session->creationTime = currentTimeInt;
                            mutex.lock();
                            session->sessionExpirationTime = (currentTimeInt + configuration.sessionExpirationTime);
                            mutex.unlock();
                            sessions.insert(session->getId(), session);
                        }

                        mutex.lock();
                        session->lastAccessedTime = currentTimeInt;
                        mutex.unlock();
                        request.session = session;
                        FilterChain chain(servlet);
                        filter != nullptr ? filter->doFilter(request, response, chain) :
                                            chain.doFilter(request, response);
                    }
                    else
                    {
                        FilterChain chain(servlet);
                        chain.doFilter(request, response);
                    }
                }
            }
        }
    }

    bool HttpReadRequest::readBody(HttpParser &parser, HttpServletRequest &request, HttpServletResponse &response)
    {
        qint64 contentLength = parser.contentLenght;
        QByteArray content(std::move(parser.body));
        mutex.lock();
        int maximumTime = configuration.timeOut / 2;        
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        mutex.unlock();

        while(true)
        {
            if(socket->waitForReadyRead(10))
                content += socket->readAll();

            int spendTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();

            if(content.size() > contentLength)
            {
                content.remove(contentLength, content.size());
                break;
            }
            else if(content.size() == contentLength)
                break;
            if(spendTime >= maximumTime)
                break;
        }
        if(content.size() > maxUploadFile)
        {
            request.getRequestDispatcher("/config/cppwebserverpages/403").forward(request, response);
            return false;
        }

        parser.body = std::move(content);

        if(parser.contentType.contains("application/x-www-form-urlencoded"))
            parser.doParseBody();
        else if(parser.multiPart)
            parser.doParseFiles();

        return true;
    }

    void HttpReadRequest::createSocket()
    {
        #ifndef QT_NO_OPENSSL
            if (sslConfiguration)
            {
                QSslSocket *sslSocket = new QSslSocket;
                sslSocket->setSslConfiguration(*sslConfiguration);
                socket = sslSocket;
                return;
            }
        #endif
        socket = new QTcpSocket;
    }
}

/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CPPWEBSERVER_H
#define CPPWEBSERVER_H

#include <QTcpServer>
#include <QSslKey>
#include <QSslCertificate>
#include <QHttpMultiPart>
#include <QMutex>
#include <QThreadPool>
#include <QTimer>
#include <atomic>
#include "qmapthreadsafety.h"
#include "httpreadrequest.h"
#include "httpservlet.h"
#include "httpsession.h"
#include "filter.h"
#include "httpservlet.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "configuration.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The CppWebServer class is a HTTP server, responsable to receive and dispatch the requisitions.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT CppWebServer : public QTcpServer
{
    Q_OBJECT
private:
    Filter *filter;
    QTimer *timer;
    QMapThreadSafety<QString, HttpServlet *> urlServlet;
    QMapThreadSafety<QString, HttpSession *> sessions;
    QSslConfiguration *sslConfiguration = nullptr;
    const int sleepTime = 10;
    bool block = false;
    /**
     * @brief Load the SSL Configuration to the server.
     */
    void loadSslConfiguration();
public:
    /**
     * @brief Load SSL configuration, configure the thread pool and the filter.
     * @param Filter *filter : Install a filter for requests on the server. Optional.
     */
    explicit CppWebServer(Filter *filter = nullptr);
    /**
     * @brief Destroys all servlets and sessions.
    */
    ~CppWebServer();
    /**
     * @brief Hitches a url to a Servlet.
     * @param const QString &url   : Url name.
     * @param HttpServlet *servlet : Servlet that will answer requests made to url.
     */
    void addUrlServlet(const QString &url, HttpServlet *servlet);
private slots:
    /**
     * @brief incomingConnection
     * @param qintptr socketfd : Socket descriptor.
     */
    void incomingConnection(qintptr socketfd) override;
    /**
     * @brief Clean expired sessions on Server.
     */
    void doClean();
};

CWF_END_NAMESPACE

#endif // CPPWEBSERVER_H

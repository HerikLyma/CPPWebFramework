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
#include <QThreadPool>
#include <QTimer>
#include <atomic>
#include "qmapthreadsafety.h"
#include "httpreadrequest.h"
#include "httpservlet.h"
#include "httpsession.h"
#include "filter.h"
#include "httpservlet.h"
#include "configuration.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The CppWebServer class is a HTTP server, responsable to receive and dispatch the requisitions.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT CppWebServer : public QTcpServer
{
    Q_OBJECT
private:
    Configuration configuration;
    Filter *filter;
    QTimer *timer;
    QThreadPool pool;
    QMapThreadSafety<QString, HttpServlet *> urlServlet;
    QMapThreadSafety<QString, HttpSession *> sessions;
    QSslConfiguration *sslConfiguration = nullptr;
    const int sleepTime = 10;
    QAtomicInteger<qint8> block = 0;    
    /**
     * @brief Load the SSL Configuration to the server.
     */
    void loadSslConfiguration();
public:
    /**
     * @brief Load SSL configuration, configure the thread pool and the filter.
     * @param Filter *filter : Install a filter for requests on the server. Optional.
     */
    explicit CppWebServer(const Configuration &configuration, Filter *filter = nullptr);
    /**
     * @brief Destroys all servlets and sessions.
    */
    ~CppWebServer();
    /**
     * @brief Hitches a url to a Servlet.
     * @param const QString &url   : Url name.
     * @param HttpServlet *servlet : Servlet that will answer requests made to url. If the filter is installed, all requests will be redirected to it and
     * it will not be possible to map the servlets through the addUrlServlet function, instead everything should be handled inside the Filter.
     */
    inline void addUrlServlet(const QString &url, HttpServlet *servlet) { urlServlet.insert(url, servlet); }
protected:
    /**
     * @brief incomingConnection
     * @param qintptr socketfd : Socket descriptor.
     */
    void incomingConnection(qintptr socketfd) override;
private slots:
    /**
     * @brief Clean expired sessions on Server.
     */
    void doClean();
};

CWF_END_NAMESPACE

#endif // CPPWEBSERVER_H

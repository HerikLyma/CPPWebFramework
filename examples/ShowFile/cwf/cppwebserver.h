/**
  @file cppwebserver.h
  @author Herik Lima
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

namespace CWF
{
    /**
     * @brief The CppWebServer class is a HTTP server, responsable to receive and dispatch the requisitions.
     */
    class CppWebServer : public QTcpServer
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
        void loadSslConfiguration();
    public:
        /**
         * @brief This is a constructor and receives the max thread number, a Filter, apath, a domain, the time out in milliseconds<br>
         * the session expire time, the clean time, and a parent.
         * @param maxThread
         * @param filter
         * @param path
         * @param domain
         * @param timeOutInMs
         * @param sessionExpirationTime
         * @param cleanupInterval
         * @param parent
         */
        explicit CppWebServer(Filter *filter = nullptr);
        ~CppWebServer();
        /**
         * @brief addUrlServlet
         * @param url
         * @param servlet
         */
        void addUrlServlet(const QString &url, HttpServlet *servlet);
    private slots:
        void incomingConnection(qintptr socketfd);
        void doClean();
    };
}

#endif // CPPWEBSERVER_H

/**
  @file httpreadrequest.h
  @author Herik Lima
*/

#ifndef HTTPREADREQUEST_H
#define HTTPREADREQUEST_H

#include <QMap>
#include <QFile>
#include <QMutex>
#include <chrono>
#include <QDateTime>
#include <QRunnable>
#include <QTcpSocket>
#include <QStringList>
#include <QSslConfiguration>
#include <memory>
#include "httpservlet.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "httpsession.h"
#include "filter.h"
#include "httpparser.h"
#include "httprequestmethod.h"
#include "filterchain.h"
#include "httpcookie.h"
#include "sessionidgenerator.h"
#include "qmapthreadsafety.h"

namespace CWF
{
    /**
     * @brief The HttpReadRequest class is created automatically by the CppWebServer and inserted <br>
     * in a QThreadPool, always when the CppWebServer has a call by a client(Browser).
     */
    class HttpReadRequest : public QRunnable
    {
        qintptr     socketDescriptor;
        QMapThreadSafety<QString, HttpServlet *> &urlServlet;
        QMapThreadSafety<QString, HttpSession *> &sessions;        
        QSslConfiguration *sslConfiguration;
        Filter      *filter;
        QTcpSocket  *socket = nullptr;
        QMutex mutex;                
        qint64 maxUploadFile;
        bool readBody(HttpParser &parser, HttpServletRequest &request, HttpServletResponse &response);
        void createSocket();
    public:
        /**
         * @brief This constructor needs to receive the parent, a socket descriptor, all the mapped servlets, all the sessions,<br>
         * a filter, the default path to the pages and resources like: xhtml pages, images, css...<br>
         * a domain, and a session expire time to the sessions(optional).
         * @param parent            : This is a pointer to QObject.
         * @param socketDescriptor  : This is a qintptr.
         * @param urlServlet        : This is a reference to a QMapThreadSafety.
         * @param sessions          : This is a reference to a QMapThreadSafety.
         * @param filter            : This is a pointer to a Filter.
         * @param path              : This is a reference to a QString.
         * @param domain            : This is a reference to a QString.
         * @param sessionExpirationTime : This is a qint64.
         */
        HttpReadRequest(qintptr socketDescriptor,
                        QMapThreadSafety<QString, HttpServlet *> &urlServlet,
                        QMapThreadSafety<QString, HttpSession *> &sessions,
                        QSslConfiguration *sslConfiguration,
                        Filter *filter);


        /**
         * @brief Starts to read the requisition.
         */

        ~HttpReadRequest();
        void run();
    };
}

#endif // HTTPREADREQUEST_H

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
#include "controller.h"
#include "session.h"
#include "filter.h"
#include "controller.h"
#include "configuration.h"
#include "request.h"
#include "response.h"
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
    QMapThreadSafety<QString, Controller *> urlController;
    QMapThreadSafety<QString, Session *> sessions;
    QSslConfiguration *ssl = nullptr;
    const int sleepTime = 10;
    QAtomicInteger<qint8> block = 0;    
public:
    /**
     * @brief Load SSL configuration, configure the thread pool and the filter.
     * @param Filter *filter : Install a filter for requests on the server. Optional.
     */
    explicit CppWebServer(const Configuration &configuration, Filter *filter = nullptr);
    /**
     * @brief Destroys all controllers and sessions.
    */
    ~CppWebServer() override;
    /**
     * @brief Hitches a url to a Controller.
     * @param const QString &url   : Url name.
     * it will not be possible to map the controllers through the addController function, instead everything should be handled inside the Filter.
     */
    template<typename CONTROLLER>
    void addController(const QString &url) noexcept
    {
        static_assert(std::is_base_of<Controller, CONTROLLER>::value, "CONTROLLER must be a descendant of Controller");
        urlController.insert(url, new CONTROLLER);
    }
protected:
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

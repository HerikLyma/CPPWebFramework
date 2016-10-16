/**
  @file httpservletrequest.h
  @author Herik Lima
*/

#ifndef HTTPSERVLETREQUEST_H
#define HTTPSERVLETREQUEST_H

#include <QThread>
#include <QTcpSocket>
#include "httpsession.h"
#include "requestdispatcher.h"
#include "filemanager.h"
#include "httpparser.h"

namespace CWF
{
    /**
     * @brief The HttpServletRequest class holds all information about a http request.
     */
    class HttpServletRequest : public QObject
    {
        friend class HttpReadRequest;
        friend class RequestDispatcher;
        QTcpSocket        *socket;
        QString  path;
        QString suffix;
        HttpSession *session = nullptr;
        HttpParser *httpParser  = nullptr;
        RequestDispatcher *requestDispatcher = nullptr;
        bool autoDeleteAttribute = false;
        QMap<QString, QObject *> attributes;
    public:
        /**
         * @brief This constructor needs to receive a reference to a QTcpSocket and QByteArray.
         * The parameter parent is optional.
         * NOTE: The CppWebServer is responsable to create the QTcpSocket, and the HttpReadRequest is
         * responsable to create a HttpReadRequest and a HttpServletResponse.
         * @param socket : This is a reference to a QTcpSocket.
         * @param path   : This is a reference to a QByteArray.
         * @param parent : This is a pointer to a QObject.
         */
        explicit HttpServletRequest(QTcpSocket &socket, const QString &path, const QString &suffix);
        /**
         * @brief Destructor.
         */
        virtual ~HttpServletRequest();
        /**
         * @brief This method add an attribute that will be passed to a xhtml page.
         * @param path  : This is a reference to a QByteArray and holds a name of a object
         * that will be used in a xhtml page.
         * @param value : This is a pointer to a QObject and holds the object
         * that will be used by the CSTLCompiler to process a xhtml page and generates its output.
         */
        void addAttribute(const QString &name, QObject *value);
        /**
         * @brief This method returns all the attributes of a HttpReadRequest.
         * @return QMap<QByteArray, QObject *>
         */
        QMap<QString, QObject *> getAttributes() const;
        /**
         * @brief This method returns a specific object given its name.
         * @param name : This is a reference to a QByteArray.
         * @return const QObject *
         */
        const QObject *getAttribute(const QString &name) const;

        const QByteArray getBody() const;
        /**
         * @brief This method returns a requestDispatcher given an specific page.
         * @param page : This is a reference to a QByteArray.
         * @return RequestDispatcher
         */
        RequestDispatcher &getRequestDispatcher(const QString &page);
        /**
         * @brief This method returns the http protocol.
         * @return QByteArray
         */
        QByteArray getProtocol() const;
        /**
         * @brief This method will clear all the attributes.
         */
        void clearAttributes();
        /**
         * @brief This method set the HttpParser.
         * @param httpParser
         */
        void setHttpParser(HttpParser &httpParser);
        /**
         * @brief This method returns the HttpParser.
         * @return HttpParser
         */
        HttpParser &getHttpParser() const;
        /**
         * @brief This method returns the requested url.
         * @return QByteArray
         */
        QByteArray getRequestURL() const;
        /**
         * @brief This method returns the requested url.
         * @return QByteArray
         */
        QByteArray getRequestURI() const;
        /**
         * @brief This method returns the user's session.
         */
        HttpSession &getSession() const;
        /**
         * @brief This method set the user's session.
         * @return HttpSession
         */
        void setSession(HttpSession &session);
        /**
         * @brief This method returns the most recent parameter from a request given an specific name.
         * @param name : This is a reference to a QByteArray.
         * @return QByteArray
         */
        QByteArray getParameter(const QByteArray &name) const;
        /**
         * @brief This method returns the parameters from a request given an specific name.
         * @param name : This is a reference to a QByteArray.
         * @return QByteArray
         */
        QByteArrayList getParameters(const QByteArray &name) const;
        /**
         * @brief This method returns a reference to the current socket.
         * @return QTcpSocket
         */
        QTcpSocket &getSocket() const;
        /**
         * @brief This method returns the auto delete attribute.
         * @return bool
         */
        bool getAutoDeleteAttribute() const;
        /**
         * @brief This method sets the auto delete attribute.
         * When the auto delete attribute is true and the HttpServletRequest is destroyed,
         * the attributes that you added will be destroyed.
         * NOTE: By default the auto delete attribute is false.
         * @param value : This sets the auto delete attribute.
         */
        void setAutoDeleteAttribute(bool value);
        /**
         * @brief This method returns the path.
         * @return QString
         */
        QString getPath() const;
        /**
         * @brief This method returns all the files that the user has sent.
         * @return QMap<QByteArray, QByteArray>
         */
        QMultiMap<QByteArray, QByteArray> getUploadedFiles() const;

        void fillQObject(QObject *object);
    };
}

#endif // HTTPSERVLETREQUEST_H

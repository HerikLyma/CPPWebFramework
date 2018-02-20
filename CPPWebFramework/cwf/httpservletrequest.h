/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef HTTPSERVLETREQUEST_H
#define HTTPSERVLETREQUEST_H

#include <QThread>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "httpparser.h"
#include "httpsession.h"
#include "filemanager.h"
#include "configuration.h"
#include "requestdispatcher.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The HttpServletRequest class holds all information about a http request.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT HttpServletRequest : public QObject
{
    friend class HttpReadRequest;
    friend class RequestDispatcher;
    QTcpSocket               *socket;
    HttpSession              *session            = nullptr;
    HttpParser               *httpParser         = nullptr;
    RequestDispatcher        *requestDispatcher  = nullptr;
    HttpServletResponse      *response           = nullptr;
    bool                     autoDeleteAttribute = false;
    QMap<QString, QObject *> attributes;
    QMapThreadSafety<QString, HttpSession *> &sessions;
    const Configuration &configuration;
public:
    /**
     * @brief This constructor needs to receive a reference to a QTcpSocket and QByteArray.
     * The parameter parent is optional.
     * NOTE: The CppWebServer is responsable to create the QTcpSocket, and the HttpReadRequest is
     * responsable to create a HttpReadRequest and a HttpServletResponse.
     */
    explicit HttpServletRequest(QTcpSocket &socket, QMapThreadSafety<QString, HttpSession *> &sessions, const Configuration &configuration);
    /**
     * @brief Destroys dynamically allocated resources.
     */
    virtual ~HttpServletRequest();
    /**
     * @brief This method add an attribute that will be passed to a xhtml page.
     * The object can be processed within a page using xhtml CSTL. For this to be possible the object must
     * inherit from QObject and methods and must be in session "public slots".
     */
    inline void addAttribute(const QString &name, QObject *value) { attributes.insert(name, value); }
    /**
     * @brief This method returns all the attributes of a HttpReadRequest.
     */
    inline QMap<QString, QObject *> getAttributes() const { return attributes; }
    /**
     * @brief This method returns a specific object given its name.     
     */
    inline const QObject *getAttribute(const QString &name) const { return attributes.contains(name) ? attributes[name] : nullptr; }
    /**
     * @brief Returns the request body.
     */
    inline const QByteArray getBody() const { return httpParser->getBody(); }
    /**
     * @brief Tries returns the body of the converted request to QJsonObject.
     */
    inline QJsonObject bodyToJsonObject() const { return QJsonDocument::fromJson(httpParser->getBody()).object(); }
    /**
     * @brief Tries returns the body of the converted request to QJsonArray.
     */
    inline QJsonArray bodyToJsonArray() const { return QJsonDocument::fromJson(httpParser->getBody()).array(); }
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
    inline QByteArray getProtocol() const { return httpParser != nullptr ? httpParser->getHttpVersion() : ""; }
    /**
     * @brief This method will clear all the attributes.
     */
    inline void clearAttributes() { attributes.clear(); }
    /**
     * @brief This method set the HttpParser.
     * @param httpParser
     */
    inline void setHttpParser(HttpParser &httpParser) { this->httpParser = &httpParser; }
    /**
     * @brief This method returns the HttpParser.
     * @return HttpParser
     */
    inline HttpParser &getHttpParser() const { return *httpParser; }
    /**
     * @brief This method returns the requested url.
     * @return QByteArray
     */
    inline QByteArray getRequestURL() const { return httpParser != nullptr ? httpParser->getUrl() : ""; }
    /**
     * @brief This method returns the requested url.
     * @return QByteArray
     */
    inline QByteArray getRequestURI() const { return httpParser != nullptr ? httpParser->getUrl() : ""; }
    /**
     * @brief This method returns the user's session.
     */
    HttpSession &getSession();
    /**
     * @brief This method set the user's session.
     * @return HttpSession
     */
    inline void setSession(HttpSession &session) { this->session = &session; }
    /**
     * @brief This method returns the most recent parameter from a request given an specific name.
     * @param name : This is a reference to a QByteArray.
     * @return QByteArray
     */
    inline QByteArray getParameter(const QByteArray &name) const { return httpParser->getParameter(name); }
    /**
     * @brief This method returns the parameters from a request given an specific name.
     * @param name : This is a reference to a QByteArray.
     * @return QByteArray
     */
    inline QByteArrayList getParameters(const QByteArray &name) const { return httpParser->getParameters(name); }
    /**
     * @brief This method returns a reference to the current socket.
     * @return QTcpSocket
     */
    inline QTcpSocket &getSocket() const { return *socket; }
    /**
     * @brief This method returns the auto delete attribute.
     * @return bool
     */
    inline bool getAutoDeleteAttribute() const { return autoDeleteAttribute; }
    /**
     * @brief This method sets the auto delete attribute.
     * When the auto delete attribute is true and the HttpServletRequest is destroyed,
     * the attributes that you added will be destroyed.
     * NOTE: By default the auto delete attribute is false.
     * @param value : This sets the auto delete attribute.
     */
    inline void setAutoDeleteAttribute(bool value) { autoDeleteAttribute = value; }
    /**
     * @brief This method returns the path.
     * @return QString
     */
    inline QString getPath() const { return configuration.getPath(); }
    /**
     * @brief This method returns all the files that the user has sent.
     * @return QMap<QByteArray, QByteArray>
     */
    inline QMultiMap<QByteArray, QByteArray> getUploadedFiles() const { return httpParser->getUploadedFiles(); }
    /**
     * @brief Fill a QObject using parameters of a HTTP message.
     * @param QObject *object : Object to be filled.
     * @par Example
     * @code
     * //----------------bmi.xhtml----------------
     *
     * <?xml version="1.0" encoding="iso-8859-1" ?>
     * <html>
     *      <head>
     *          <title>Body Mass Index (BMI)</title>
     *      </head>
     *      <body>
     *          <form method="POST" action="/bmi">
     *              Name<br/><input type="text" name="name"/><br/>
     *              Mass(KG)<br/><input type="text" name="mass"/><br/>
     *              Height(m)<br/><input type="text" name="height"/><br/><br/>
     *              <input type="submit" name="submit" value="Calculate"/>
     *          </form>
     *      </body>
     *  </html>
     *
     * //----------------bmiresults.xhtml----------------
     *
     * <?xml version="1.0" encoding="iso-8859-1" ?>
     * <html>
     *      <head>
     *          <title>Body Mass Index (BMI) - Results</title>
     *      </head>
     *      <body>
     *          Name: <out value="#{user.getName}"/><br/>
     *          Mass(KG): <out value="#{user.getMass}"/><br/>
     *          Height(m): <out value="#{user.getHeight}"/><br/>
     *          BMI: <out value="#{user.getBmi}"/><br/>
     *          Category: <out value="#{user.getCategory}"/>
     *      </body>
     * </html>
     *
     * //----------------user.h----------------
     *
     * #ifndef USER_H
     * #define USER_H
     *
     * #include <QObject>
     * #include <QString>
     *
     * class User : public QObject
     * {
     *     Q_OBJECT
     * private:
     *     QString name;
     *     QString category;
     *     double mass = 0;
     *     double height = 0;
     *     double bmi = 0;
     * public:
     *     explicit User(QObject *parent = 0) : QObject(parent)
     *     {
     *     }
     * public slots:
     *     QString getName() const
     *     {
     *         return name;
     *     }
     *     void setName(const QString &value)
     *     {
     *         name = value;
     *     }
     *     QString getCategory() const
     *     {
     *         return category;
     *     }
     *     double getMass() const
     *     {
     *         return mass;
     *     }
     *     void setMass(double value)
     *     {
     *         mass = value;
     *     }
     *     double getHeight() const
     *     {
     *         return height;
     *     }
     *     void setHeight(double value)
     *     {
     *         height = value;
     *     }
     *     double getBmi()
     *     {
     *         bmi = height != 0 ? mass / (height * height) : 0;
     *
     *         if(bmi <= 15)
     *         {
     *             category = "Very severely underweight";
     *         }
     *         else if(bmi > 15 && bmi <= 16)
     *         {
     *             category = "Severely underweight";
     *         }
     *         else if(bmi > 16 && bmi <= 18.5)
     *         {
     *             category = "Underweight";
     *         }
     *         else if(bmi > 18.5 && bmi <= 25)
     *         {
     *             category = "Normal (healthy weight)";
     *         }
     *         else if(bmi > 25 && bmi <= 30)
     *         {
     *             category = "Overweight";
     *         }
     *         else if(bmi > 30 && bmi <= 35)
     *         {
     *             category = "Obese Class I (Moderately obese)";
     *         }
     *         else if(bmi > 35 && bmi <= 40)
     *         {
     *             category = "Obese Class II (Severely obese)";
     *         }
     *         else
     *         {
     *             category = "Obese Class III (Very severely obese)";
     *         }
     *
     *         return bmi;
     *     }
     * };
     *
     * #endif // USER_H
     *
     * //----------------bmicontroller.h----------------
     *
     * #ifndef BMISERVLET_H
     * #define BMISERVLET_H
     *
     * #include "cwf/httpservlet.h"
     * #include "cwf/httpservletrequest.h"
     * #include "cwf/httpservletresponse.h"
     * #include "entities/user.h"
     *
     * class BmiServlet : public CWF::HttpServlet
     * {
     * public:
     *     void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response) override
     *     {
     *         request.getRequestDispatcher("/pages/bmi").forward(request, response);
     *     }
     *     void doPost(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response) override
     *     {
     *         User user;
     *         request.fillQObject(&user);
     *         request.addAttribute("user", &user);
     *         request.getRequestDispatcher("/pages/bmiresults").forward(request, response);
     *     }
     * };
     *
     * #endif // BMISERVLET_H
     *
     * //----------------main.cpp----------------
     *
     * #include <QCoreApplication>
     * #include <cwf/cppwebapplication.h>
     * #include <servlets/bmiservlet.h>
     *
     * int main(int argc, char *argv[])
     * {
     *     CWF::CppWebApplication server(argc, argv, "PATH_TO_SERVER_FOLDER");
     *
     *     server.addUrlServlet("/bmi", new BmiServlet);
     *
     *     return server.start();
     * }
     * @endcode
     */
    void fillQObject(QObject *object);
};

CWF_END_NAMESPACE

#endif // HTTPSERVLETREQUEST_H

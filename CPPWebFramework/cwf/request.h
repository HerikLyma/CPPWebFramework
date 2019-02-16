/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef Request_H
#define Request_H

#include <QThread>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "httpparser.h"
#include "urlencoder.h"
#include "session.h"
#include "filemanager.h"
#include "configuration.h"
#include "requestdispatcher.h"
#include "cppwebframework_global.h"


CWF_BEGIN_NAMESPACE
/**
 * @brief The Request class holds all information about a http request.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT Request
{
    friend class HttpReadRequest;
    friend class RequestDispatcher;
    QTcpSocket         &socket;
    Session            *session            = nullptr;
    HttpParser         *httpParser         = nullptr;
    RequestDispatcher  *requestDispatcher  = nullptr;
    Response           *response           = nullptr;
    QMap<QString, QObject *> attributes;
    QMapThreadSafety<QString, Session *> &sessions;
    const Configuration &configuration;
public:
    /**
     * @brief This constructor needs to receive a reference to a QTcpSocket and QByteArray.
     * The parameter parent is optional.
     * NOTE: The CppWebServer is responsable to create the QTcpSocket, and the HttpReadRequest is
     * responsable to create a HttpReadRequest and a Response.
     */
    explicit Request(QTcpSocket &socket, QMapThreadSafety<QString, Session *> &sessions, const Configuration &configuration);
    /**
     * @brief Destroys dynamically allocated resources.
     */
    ~Request() noexcept;
    /**
     * @brief This method add attributes that will be passed to a view page.
     * The object can be processed within a page using view CSTL. For this to be possible the object must
     * inherit from QObject and methods and must be in session "public slots".
     */
    inline void addAttribute(const std::initializer_list<QPair<QString, QObject *>> &value) noexcept
    {
        std::for_each(value.begin(), value.end(), [&](const QPair<QString, QObject *> &v){attributes.insert(v.first, v.second);});
    }
    /**
     * @brief This method add an attribute that will be passed to a view page.
     * The object can be processed within a page using view CSTL. For this to be possible the object must
     * inherit from QObject and methods and must be in session "public slots".
     */
    inline void addAttribute(const QString &name, QObject *value) noexcept { attributes.insert(name, value); }
    /**
     * @brief This method returns all the attributes of a HttpReadRequest.
     */
    inline QMap<QString, QObject *> getAttributes() const noexcept { return attributes; }
    /**
     * @brief This method returns a specific object given its name.     
     */
    inline const QObject *getAttribute(const QString &name) const noexcept { return attributes.contains(name) ? attributes[name] : nullptr; }
    /**
     * @brief Returns the request body.
     */
    inline const QByteArray getBody() const noexcept { return httpParser->getBody(); }
    /**
     * @brief Tries returns the body of the converted request to QJsonObject.
     */
    inline QJsonObject bodyToJsonObject() const noexcept { return QJsonDocument::fromJson(httpParser->getBody()).object(); }
    /**
     * @brief Tries returns the body of the converted request to QJsonArray.
     */
    inline QJsonArray bodyToJsonArray() const noexcept { return QJsonDocument::fromJson(httpParser->getBody()).array(); }
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
    inline QByteArray getProtocol() const noexcept { return httpParser != nullptr ? httpParser->getHttpVersion() : ""; }
    /**
     * @brief This method will clear all the attributes.
     */
    inline void clearAttributes() noexcept { attributes.clear(); }
    /**
     * @brief This method set the HttpParser.
     * @param httpParser
     */
    inline void setHttpParser(HttpParser &httpParser) noexcept { this->httpParser = &httpParser; }
    /**
     * @brief This method returns the HttpParser.
     * @return HttpParser
     */
    inline HttpParser &getHttpParser() const noexcept { return *httpParser; }
    /**
     * @brief This method returns the requested url.
     * @return QByteArray
     */
    inline QByteArray getRequestURL() const noexcept{ return httpParser != nullptr ? httpParser->getUrl() : ""; }
    /**
     * @brief This method returns the requested url.
     * @return QByteArray
     */
    inline QByteArray getRequestURI() const noexcept { return httpParser != nullptr ? httpParser->getUrl() : ""; }
    /**
     * @brief This method returns the user's session.
     */
    Session &getSession();
    /**
     * @brief This method set the user's session.
     * @return Session
     */
    inline void setSession(Session &session) noexcept { this->session = &session; }
    /**
     * @brief This method returns the most recent parameter from a request given an specific name.
     * @param name : This is a reference to a QByteArray.
     * @param decode : If true, decode the parameter.
     * @return QByteArray
     */
    QByteArray getParameter(const QByteArray &name, bool urlDecode = true, bool replacePlusForSpace = true) const noexcept
    {
        return httpParser->getParameter(name, urlDecode, replacePlusForSpace);
    }
    /**
     * @brief This method returns the parameters from a request given an specific name.
     * @param name : This is a reference to a QByteArray.     
     * @return QByteArray
     */
    inline QByteArrayList getParameters(const QByteArray &name) const noexcept { return httpParser->getParameters(name); }
    /**
     * @brief This method returns a reference to the current socket.
     * @return QTcpSocket
     */
    inline QTcpSocket &getSocket() const noexcept { return socket; }
    /**
     * @brief This method returns the path.
     * @return QString
     */
    inline QString getPath() const noexcept { return configuration.getPath(); }
    /**
     * @brief This method returns all the files that the user has sent.
     * @return QMap<QByteArray, QByteArray>
     */
    inline QMultiMap<QByteArray, QByteArray> getUploadedFiles() const noexcept { return httpParser->getUploadedFiles(); }
    /**
     * @brief Fill a QObject using parameters of a HTTP message.
     * @param QObject *object : Object to be filled.
     * @par Example
     * @code
     * //----------------bmi.view----------------
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
     * //----------------bmiresults.view----------------
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
     * #ifndef BMICONTROLLER_H
     * #define BMICONTROLLER_H
     *
     * #include "cwf/controller.h"
     * #include "cwf/request.h"
     * #include "cwf/response.h"
     * #include "entities/user.h"
     *
     * class BmiController : public CWF::Controller
     * {
     * public:
     *     void doGet(CWF::Request &request, CWF::Response &response) override
     *     {
     *         request.getRequestDispatcher("/pages/bmi").forward(request, response);
     *     }
     *     void doPost(CWF::Request &request, CWF::Response &response) override
     *     {
     *         User user;
     *         request.fillQObject(&user);
     *         request.addAttribute("user", &user);
     *         request.getRequestDispatcher("/pages/bmiresults.view").forward(request, response);
     *     }
     * };
     *
     * #endif // BMICONTROLLER_H
     *
     * //----------------main.cpp----------------
     *
     * #include <QCoreApplication>
     * #include <cwf/cppwebapplication.h>
     * #include <controllers/bmicontroller.h>
     *
     * int main(int argc, char *argv[])
     * {
     *     CWF::CppWebApplication server(argc, argv, "PATH_TO_SERVER_FOLDER");
     *
     *     server.addUrlController<BmiController>("/bmi");
     *
     *     return server.start();
     * }
     * @endcode
     */
    void fillQObject(QObject *object, bool urlDecode = true, bool replacePlusForSpace = true);

    void fillQObject(QObject *object,
                     const QMap<QByteArray, QByteArray> &parameters,
                     bool urlDecode = true, bool replacePlusForSpace = true);
};

CWF_END_NAMESPACE

#endif // Request_H

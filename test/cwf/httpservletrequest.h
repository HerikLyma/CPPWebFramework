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
         * @brief Destroys dynamically allocated resources.
         */
        virtual ~HttpServletRequest();
        /**
         * @brief This method add an attribute that will be passed to a xhtml page.
         * The object can be processed within a page using xhtml CSTL. For this to be possible the object must
         * inherit from QObject and methods and must be in session "public slots".
         * @param const QString &name :
         * @param QObject *value      :
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
         * @return const QObject * : Attributte's name.
         */
        const QObject *getAttribute(const QString &name) const;
        /**
         * @brief Returns
         * @return
         */
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
         *     CWF::CppWebApplication server(argc,
         *                                   argv,
         *                                   CWF::Configuration("/home/herik/CPPWebFramework/examples/FillObjectBMI/server"));
         *
         *     server.addUrlServlet("/bmi", new BmiServlet);
         *
         *     return server.start();
         * }
         * @endcode
         */
        void fillQObject(QObject *object);
    };
}

#endif // HTTPSERVLETREQUEST_H

/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

/**
  * @mainpage The C++ Web Framework
  * The C++ Web Framework was created by Herik Lima and Marcelo Eler at the end of 2015 and aims to provide
  * a set of classes that allow you to create targeted web applications, used C ++ with Qt.
  */

#ifndef CPPWEBAPPLICATION_H
#define CPPWEBAPPLICATION_H

#include <QString>
#include <QCoreApplication>
#include <QMessageLogContext>
#include "cppwebserver.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief This class is responsible for encapsulating the QCoreApplication, the
 * CppWebServer and configure the server logging mechanism.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT CppWebApplication
{
    QCoreApplication application;
    Configuration    configuration;
    CppWebServer     *server;
    CppWebApplication(const CppWebApplication &other) = delete;
    CppWebApplication &operator=(const CppWebApplication &other) = delete;        
public:
    /**
     * @brief Constructs a QCoreApplication, a CppWebServer and install the message handler.
     * if the server folder's path was not found in the serverPath, it will look into the executable's folder.
     * @param int argc                    : Main function parameter used to build QCoreApplication.
     * @param char *argv[]                : Main function parameter used to build QCoreApplication.
     * @param const Configuration &config : Used to set the parameters of the server.
     * @param Filter *filter              : Install a filter for requests on the server. Optional.
     */
    CppWebApplication(int argc, char *argv[], const QString &serverPath, Filter *filter = nullptr);
    /**
     * @brief Destroys the server dynamically allocated.
     */
    ~CppWebApplication();
    /**
     * @brief Hitches a url to a Servlet.
     * @param const QString &url   : Url name.
     * @param HttpServlet *servlet : Servlet that will answer requests made to url.
     * @par Example
     * @code
     * #include <QCoreApplication>
     * #include <servlets/helloworldservlet.h>
     * #include <cwf/cppwebapplication.h>
     *
     * int main(int argc, char *argv[])
     * {
     *      CWF::CppWebApplication server(argc, argv, CWF::Configuration("/home/herik/CPPWebFramework/examples/HelloWorld/server"));
     *
     *      server.addUrlServlet("/hello", new HelloWorldServlet);
     *      return server.start();
     * }
     * @endcode
     */
    inline void addUrlServlet(const QString &url, HttpServlet *servlet) { server->addUrlServlet(url, servlet); }
    /**
     * @brief Starts the server and QCoreApplication.
     * @return int : Returns -1 if it fails.
     */
    int start();
};

CWF_END_NAMESPACE

#endif // CPPWEBAPPLICATION_H

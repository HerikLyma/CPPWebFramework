/**
  @file cppwebapplication.h
  @author Herik Lima
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

namespace CWF
{
    /**
     * @brief This class is responsible for encapsulating the QCoreApplication, the
     * CppWebServer and configure the server logging mechanism.
     */
    class CppWebApplication
    {
        QCoreApplication application;
        CppWebServer     *server;
        /**
         * @brief This method is the message handler that will be installed in qInstallMessageHandler to direct
         * all program message flow to the log file.
         * @param QtMsgType type                       : Describes the messages that can be sent to a message handler.
         * @param const QMessageLogContext &logContext : Provides additional information about a log message.
         * @param const QString &msg                   : The message that will be written to the log file.
         */
        static void writeLog(QtMsgType type, const QMessageLogContext &logContext, const QString &msg);
    public:
        /**
         * @brief Constructs a QCoreApplication, a CppWebServer and install the message handler.
         * @param int argc                    : Main function parameter used to build QCoreApplication.
         * @param char *argv[]                : Main function parameter used to build QCoreApplication.
         * @param const Configuration &config : Used to set the parameters of the server.
         * @param Filter *filter              : Install a filter for requests on the server. Optional.
         */
        CppWebApplication(int argc, char *argv[], const Configuration &config, Filter *filter = nullptr);
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
        void addUrlServlet(const QString &url, HttpServlet *servlet);        
        /**
         * @brief Starts the server and QCoreApplication.
         * @return int : Returns -1 if it fails.
         */
        int start();
    };
}

#endif // CPPWEBAPPLICATION_H

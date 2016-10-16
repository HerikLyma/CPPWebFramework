/**
  @file cppwebapplication.h
  @author Herik Lima
*/

#ifndef CPPWEBAPPLICATION_H
#define CPPWEBAPPLICATION_H

#include <QString>
#include <QCoreApplication>
#include <QMessageLogContext>
#include "cppwebserver.h"

namespace CWF
{
    class CppWebApplication
    {
        QCoreApplication application;
        CppWebServer     *server;
        static void configureLog(QtMsgType type, const QMessageLogContext &logContext, const QString &msg);
    public:
        CppWebApplication(int argc, char *argv[], const Configuration &config, Filter *filter = nullptr);
        ~CppWebApplication();
        void addUrlServlet(const QString &url, HttpServlet *servlet);
        int start();
    };
}

#endif // CPPWEBAPPLICATION_H

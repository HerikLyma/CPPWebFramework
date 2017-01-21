/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cppwebapplication.h"
#include "cppwebservlet.h"

namespace CWF
{
    CWF::Configuration configuration;

    CppWebApplication::CppWebApplication(int argc, char *argv[],
                                         const Configuration &config,
                                         Filter *filter) : application(argc, argv)
    {
        configuration = config;
        server = new CppWebServer(filter);
        qInstallMessageHandler(CppWebApplication::writeLog);

        if(configuration.accessServerPages)
        {
            server->addUrlServlet("/examples"     , new CppWebServlet);
            server->addUrlServlet("/authors"      , new CppWebServlet);
            server->addUrlServlet("/documentation", new CppWebServlet);
            server->addUrlServlet("/ssl"          , new CppWebServlet);
            server->addUrlServlet("/index"        , new CppWebServlet);
        }
    }

    CppWebApplication::~CppWebApplication()
    {
        if(!server)
            delete server;
    }

    void CppWebApplication::addUrlServlet(const QString &url, HttpServlet *servlet)
    {
        server->addUrlServlet(url, servlet);
    }

    int CppWebApplication::start()
    {
        if(!server->listen(configuration.host, configuration.port))
        {
            qDebug() << "Error: " << server->errorString() << "\n";
            qDebug() << "Server offline\n";
            return -1;
        }

        qDebug() << "Server online\n";
        return application.exec();
    }

    void CppWebApplication::writeLog(QtMsgType type, const QMessageLogContext &logContext, const QString &msg)
    {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        FileManager fileManager;
        fileManager.removeLastBar(configuration.logFilePath);

        QFile file(configuration.logFilePath + "/CPPWebServer.log");

        if(file.open(QIODevice::Append))
        {
            QTextStream out(&file);
            QString date = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss:zzz");
            out << "Date: "       << date;
            out << "\nCategory: " << logContext.category;
            out << "\nFile: "     << logContext.file;
            out << "\nFunction: " << logContext.function;
            out << "\nVersion: "  << logContext.version;
            out << "\nMessage: "  << msg << "\n\n";

            if(type == QtFatalMsg)
            {
                out << "\nFATAL: SERVER OFFLINE\n\n";
                file.close();
                abort();
            }
            file.close();
        }
    }
}

/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cppwebapplication.h"
#include "cppwebservlet.h"

CWF_BEGIN_NAMESPACE

QPair<QString, qint64> getFileAndMaxSize()
{
    QPair<QString, qlonglong> info;

#ifdef Q_OS_WIN32
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
        info.first  = qEnvironmentVariable(CONFIGURATION::CPP_LOG_VAR.toStdString().data());
        info.second = QString(qEnvironmentVariable(CONFIGURATION::CPP_LOG_MAX_VAR.toStdString().data())).toInt();
    #else
        info.first  = qgetenv(CONFIGURATION::CPP_LOG_VAR.toStdString().data());
        info.second = QByteArray(qgetenv(CONFIGURATION::CPP_LOG_MAX_VAR.toStdString().data())).toInt();
    #endif
#else
    info.first  = qgetenv(CONFIGURATION::CPP_LOG_VAR.toStdString().data());
    info.second = QByteArray(qgetenv(CONFIGURATION::CPP_LOG_MAX_VAR.toStdString().data())).toInt();
#endif

    if(info.second <= 0)
    {
        info.second = 20000000;
    }
    return info;
}

void writeLog(QtMsgType type, const QMessageLogContext &logContext, const QString &msg)
{
    QPair<QString, qint64> info(getFileAndMaxSize());
    QFile file(info.first);

    if(file.size() > info.second)
    {
        file.resize(0);
    }

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

CppWebApplication::CppWebApplication(int argc, char *argv[],
                                     const QString &serverPath,
                                     Filter *filter) : application(argc, argv), configuration(serverPath)
{
    if(configuration.isValid())
    {               
        qunsetenv(CONFIGURATION::CPP_LOG_VAR.toStdString().data());
        qunsetenv(CONFIGURATION::CPP_LOG_MAX_VAR.toStdString().data());

        qputenv(CONFIGURATION::CPP_LOG_VAR.toStdString().data(), configuration.logFilePath.toLatin1());
        qputenv(CONFIGURATION::CPP_LOG_MAX_VAR.toStdString().data(), QByteArray::number(configuration.maxLogFile));

        QPair<QString, qint64> info(getFileAndMaxSize());
        if(!QFile(info.first).exists())
        {
            configuration.valid = false;
            qDebug() << "Path not found to log file: " << configuration.getLogFilePath();
            qDebug() << "Note: Use only US-ASCII characters for the serverPath.";
        }

        if(configuration.isValid())
        {
            qInstallMessageHandler(writeLog);
            server = new CppWebServer(configuration, filter);

            if(configuration.accessServerPages)
            {
                server->addUrlServlet("/examples"     , new CppWebServlet);
                server->addUrlServlet("/authors"      , new CppWebServlet);
                server->addUrlServlet("/documentation", new CppWebServlet);
                server->addUrlServlet("/ssl"          , new CppWebServlet);
                server->addUrlServlet("/index"        , new CppWebServlet);
            }
        }
    }
    else
    {
        qDebug() << "CPPWeb.ini not found. Please copy the CWF server folder to your project.";
    }
}

CppWebApplication::~CppWebApplication()
{
    if(!server)
        delete server;
}

int CppWebApplication::start()
{
    if(!configuration.isValid())
        return -1;
    if(!server->listen(configuration.host, configuration.port))
    {
        qDebug() << "Error: " << server->errorString() << "\n";
        qDebug() << "Server offline\n";
        return -1;
    }

    qDebug() << "Server online\n";
    return application.exec();
}

CWF_END_NAMESPACE

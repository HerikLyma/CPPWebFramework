/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "request.h"
#include "metaclassparser.h"
#include "constants.h"
#include "response.h"
#include "urlencoder.h"
#include <QUuid>
//  clazy:excludeall=connect-not-normalized
CWF_BEGIN_NAMESPACE

Request::Request(QTcpSocket &socket,
                 QMapThreadSafety<QString, Session *> &sessions,
                 const Configuration &configuration) : socket(socket),
                                                       sessions(sessions),
                                                       configuration(configuration)
{    
}

Request::~Request() noexcept
{
    delete requestDispatcher;
}

void Request::fillQObject(QObject *object, bool urlDecode, bool replacePlusForSpace)
{
    fillQObject(object, httpParser->getParameters(), urlDecode, replacePlusForSpace);
}

void Request::fillQObject(QObject *object, const QMap<QByteArray, QByteArray> &parameters, bool urlDecode, bool replacePlusForSpace)
{
    MetaClassParser meta(object);

    for(QMap<QByteArray, QByteArray>::const_iterator it = parameters.constBegin(); it != parameters.constEnd(); ++it)
    {
        QString method = it.key();
        if(method.size() > 0)
        {
            QString value = it.value();

            method[0] = method[0].toUpper();
            method = GET_SET::SET_LOWER + method;

            QString parameterType(meta.getParameterType(method));

            if(parameterType == CSTL::SUPPORTED_TYPES::QSTRING)
            {
                if(urlDecode)
                    value = URLEncoder::paramDecode(value.toLatin1(), replacePlusForSpace);
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(QString, value));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::STD_STRING)
            {
                if(urlDecode)
                    value = URLEncoder::paramDecode(value.toLatin1(), replacePlusForSpace);
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(std::string, value.toStdString()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::BOOL)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(bool, value.toInt() == 0));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::CHAR)
            {
                if(value.isEmpty())
                    value.push_back(' ');
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(char, value.toStdString()[0]));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::UNSIGNED_CHAR)
            {
                if(value.isEmpty())
                    value.push_back(' ');
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned char, static_cast<unsigned char>(value.toStdString()[0])));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::SHORT)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(short, static_cast<short>(value.toInt())));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::UNSIGNED_SHORT)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned short, static_cast<unsigned short>(value.toInt())));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::INT)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(int, value.toInt()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::UNSIGNED_INT)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned int, value.toUInt()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::LONG)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(long, value.toLong()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::UNSIGNED_LONG)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned long, value.toULong()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::LONG_LONG)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(long long, value.toLongLong()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::UNSIGNED_LONG_LONG)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned long long, value.toULongLong()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::FLOAT)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(float, value.toFloat()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::DOUBLE)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(double, value.toDouble()));
            }
        }
    }
}

RequestDispatcher &Request::getRequestDispatcher(const QString &page)
{
    delete requestDispatcher;
    requestDispatcher = new RequestDispatcher(configuration.getPath() + page);
    return *requestDispatcher;
}

Session &Request::getSession()
{
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    qint64 currentTimeInt = QDateTime::currentMSecsSinceEpoch();
    qint64 expiration = configuration.getSessionExpirationTime();
    if(!session)
    {
        QByteArray sessionId  = httpParser->getSessionId();
        if(sessionId.isEmpty() || !sessions.contains(sessionId))
        {
            sessionId = QUuid::createUuid().toString().toLocal8Bit();
            response->addCookie(QNetworkCookie(HTTP::SESSION_ID, sessionId));
            session = new Session(sessionId, expiration);
            session->creationTime = currentTimeInt;            
            session->sessionExpirationTime = (currentTimeInt + expiration);
            sessions.insert(session->getId(), session);
        }
        else
        {
            session = sessions[sessionId];
        }
    }
    session->expired          = (currentTimeInt >= session->sessionExpirationTime);
    session->lastAccessedTime = currentTimeInt;
    if(!session->expired)
    {
        session->sessionExpirationTime = (currentTimeInt + expiration);
    }
    return *session;
}

CWF_END_NAMESPACE

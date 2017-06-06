/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "httpservletrequest.h"
#include "metaclassparser.h"
#include "constants.h"
#include "httpservletresponse.h"
#include "configuration.h"
#include <QUuid>

CWF_BEGIN_NAMESPACE

extern QMutex mutex;
extern Configuration configuration;

HttpServletRequest::HttpServletRequest(QTcpSocket &socket,
                                       const QString &path,
                                       QMapThreadSafety<QString, HttpSession *> &sessions) : socket(&socket),
                                                                                             path(path),
                                                                                             sessions(sessions)
{
}

HttpServletRequest::~HttpServletRequest()
{
    if(requestDispatcher)
        delete requestDispatcher;
}

QMap<QString, QObject *> HttpServletRequest::getAttributes() const
{
    return attributes;
}

QMultiMap<QByteArray, QByteArray> HttpServletRequest::getUploadedFiles() const
{
    return httpParser->getUploadedFiles();
}

void HttpServletRequest::fillQObject(QObject *object)
{
    QMap<QByteArray, QByteArray> parameters(std::move(httpParser->getParameters()));
    MetaClassParser meta(object);

    for(QMap<QByteArray, QByteArray>::iterator it = parameters.begin(); it != parameters.end(); ++it)
    {
        QString method = it.key();
        if(method.size() > 0)
        {
            QString value = it.value();

            method[0] = method[0].toUpper();
            method = GET_SET::SET_LOWER + method;

            QString parameterType(std::move(meta.getParameterType(method)));

            if(parameterType == CSTL::SUPPORTED_TYPES::QSTRING)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(QString, value));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::STD_STRING)
            {
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
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned char, (unsigned char)value.toStdString()[0]));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::CHAR_POINTER)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(char*, (char *)value.toStdString().data()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::UNSIGNED_CHAR_POINTER)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned char*, (unsigned char *)value.toStdString().data()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::SHORT)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(short, (short)value.toInt()));
            }
            else if(parameterType == CSTL::SUPPORTED_TYPES::UNSIGNED_SHORT)
            {
                QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned short, value.toInt()));
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

void HttpServletRequest::addAttribute(const QString &name, QObject *value)
{
    attributes.insert(name, value);
}

const QObject *HttpServletRequest::getAttribute(const QString &name) const
{
    return attributes.contains(name) ? attributes[name] : nullptr;
}

const QByteArray HttpServletRequest::getBody() const
{
    return httpParser->getBody();
}

RequestDispatcher &HttpServletRequest::getRequestDispatcher(const QString &page)
{
    if(requestDispatcher)
        delete requestDispatcher;

    requestDispatcher = new RequestDispatcher(this->path + page);
    return *requestDispatcher;
}

QByteArray HttpServletRequest::getProtocol() const
{
    return httpParser != nullptr ? httpParser->getHttpVersion() : "";
}

void HttpServletRequest::clearAttributes()
{
    attributes.clear();
}

void HttpServletRequest::setHttpParser(HttpParser &httpParser)
{
    this->httpParser = &httpParser;
}

HttpParser &HttpServletRequest::getHttpParser() const
{
    return *httpParser;
}

QByteArray HttpServletRequest::getRequestURL() const
{
    return httpParser != nullptr ? httpParser->getUrl() : "";
}

QByteArray HttpServletRequest::getRequestURI() const
{
    return httpParser != nullptr ? httpParser->getUrl() : "";
}

HttpSession &HttpServletRequest::getSession()
{
    qint64 currentTimeInt = QDateTime::currentMSecsSinceEpoch();
    if(!session)
    {
        QByteArray sessionId  = httpParser->getSessionId();
        if(sessionId.isEmpty() || !sessions.contains(sessionId))
        {
            sessionId = QUuid::createUuid().toString().toLocal8Bit();
            response->addCookie(HttpCookie(HTTP::SESSION_ID, sessionId));
            session = new HttpSession(sessionId);
            session->creationTime = currentTimeInt;
            session->sessionExpirationTime = (currentTimeInt + configuration.getSessionExpirationTime());
            sessions.insert(session->getId(), session);
        }
        else
        {
            session = sessions[sessionId];
        }
    }
    session->expired          = (currentTimeInt >= session->sessionExpirationTime);
    session->lastAccessedTime = currentTimeInt;
    return *session;
}

void HttpServletRequest::setSession(HttpSession &session)
{
    this->session = &session;
}

QByteArray HttpServletRequest::getParameter(const QByteArray &name) const
{
    return httpParser->getParameter(name);
}

QByteArrayList HttpServletRequest::getParameters(const QByteArray &name) const
{
    return httpParser->getParameters(name);
}

QTcpSocket &HttpServletRequest::getSocket() const
{
    return *socket;
}

bool HttpServletRequest::getAutoDeleteAttribute() const
{
    return autoDeleteAttribute;
}

void HttpServletRequest::setAutoDeleteAttribute(bool value)
{
    autoDeleteAttribute = value;
}

QString HttpServletRequest::getPath() const
{
    return path;
}

CWF_END_NAMESPACE

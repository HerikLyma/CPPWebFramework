/**
  @file httpservletrequest.cpp
  @author Herik Lima
*/

#include "httpservletrequest.h"
#include "metaclassparser.h"

namespace CWF
{
    HttpServletRequest::HttpServletRequest(QTcpSocket &socket,
                                           const QString &path,
                                           const QString &suffix) : socket(&socket),
                                                                    path(path),
                                                                    suffix(suffix)
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
                method = "set" + method;

                QString parameterType(std::move(meta.getParameterType(method)));

                if(parameterType == "QString")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(QString, value));
                }
                else if(parameterType == "std::string")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(std::string, value.toStdString()));
                }
                else if(parameterType == "bool")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(bool, value.toInt() == 0));
                }
                else if(parameterType == "char")
                {
                    if(value.isEmpty())
                        value.push_back(' ');
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(char, value.toStdString()[0]));
                }
                else if(parameterType == "unsigned char")
                {
                    if(value.isEmpty())
                        value.push_back(' ');
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned char, (unsigned char)value.toStdString()[0]));
                }
                else if(parameterType == "char*")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(char*, (char *)value.toStdString().data()));
                }
                else if(parameterType == "unsigned char*")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned char*, (unsigned char *)value.toStdString().data()));
                }
                else if(parameterType == "short")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(short, (short)value.toInt()));
                }
                else if(parameterType == "unsigned short")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned short, value.toInt()));
                }
                else if(parameterType == "int")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(int, value.toInt()));
                }
                else if(parameterType == "unsigned int")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned int, value.toUInt()));
                }
                else if(parameterType == "long")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(long, value.toLong()));
                }
                else if(parameterType == "unsigned long")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned long, value.toULong()));
                }
                else if(parameterType == "long long")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(long long, value.toLongLong()));
                }
                else if(parameterType == "unsigned long long")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(unsigned long long, value.toULongLong()));
                }
                else if(parameterType == "float")
                {
                    QMetaObject::invokeMethod(object, method.toStdString().data(), Q_ARG(float, value.toFloat()));
                }
                else if(parameterType == "double")
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

        requestDispatcher = new RequestDispatcher(this->path + page + suffix);
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

    HttpSession &HttpServletRequest::getSession() const
    {
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
}

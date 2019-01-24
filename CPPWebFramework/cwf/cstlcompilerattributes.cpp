/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cstlcompilerattributes.h"
#include "constants.h"
#include <QVariant>
#include "metaclassparser.h"
//  clazy:excludeall=connect-not-normalized
CWF_BEGIN_NAMESPACE

CSTLCompilerAttributes::CSTLCompilerAttributes(QMap<QString, QObject *> &objects) : objects(objects)
{
}

QString CSTLCompilerAttributes::buildAttributes(QMap<QString, QString> &attr, bool keyValue)
{
    QString htmlOut;
    for(QMap<QString, QString>::iterator it = attr.begin(); it != attr.end(); ++it)
    {
        compileAttributes(attr);
        if(keyValue)
            htmlOut += " " + it.key() + "=\"" + it.value() + "\"";
        else
            htmlOut += it.value();
    }
    return htmlOut;
}

void CSTLCompilerAttributes::compileAttributes(QMap<QString, QString> &attr)
{
    for(QMap<QString, QString>::iterator it = attr.begin(); it != attr.end(); ++it)
    {
        QString outPutText;
        QString &value = it.value();
        compile(value, outPutText);
        value = outPutText;
        /*
        //Compile at runtime
        if(value.startsWith("#{") && value.endsWith("}"))
        {
            value.replace("#{", "").replace("}", "");
            Properties prop(value);
            if(!objects.contains(prop.m_class))
            {
                value = "***ERROR - OBJECT " + prop.m_class + " DOES NOT EXIST.***";
            }
            else
            {
                QObject *object = objects[prop.m_class];
                bool ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(QString, value));
                if(!ok)
                {
                    value = "***ERROR - METHOD " + prop.m_method + " .***";
                }
            }
        }
        */
    }
}

void CSTLCompilerAttributes::compile(QString &text, QString &outPutText)
{
    bool start = false;
    int size = text.size();
    QString expr;

    for(int i = 0; i < size; ++i)
    {
        QChar ch = text[i];
        if(ch == '#')
        {
            if((i + 1) < size)
            {
                QChar c = text[i + 1];
                if(c == '{')
                {
                    start = true;
                }
            }
        }
        else if(ch == '}')
        {
            if(start)
            {
                start = false;
                expr.replace("#{", "");
                Properties prop(expr);
                if(!objects.contains(prop.m_class))
                {
                    outPutText += "***ERROR - OBJECT " + prop.m_class + " DOES NOT EXIST.***";
                }
                else
                {
                    QString value;
                    QObject *object = objects[prop.m_class];
                    bool ok = false;
                    MetaClassParser metaClassParser(object);
                    QString methodReturnType(metaClassParser.getReturnType(prop.m_method + "()"));

                    if(!methodReturnType.isEmpty())
                    {
                        if(methodReturnType == CSTL::SUPPORTED_TYPES::QSTRING)
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(QString, value));
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::STD_STRING)
                        {
                            std::string returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(std::string, returnValue));
                            value = returnValue.data();
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::BOOL)
                        {
                            bool returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(bool, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::CHAR)
                        {
                            char returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(char, returnValue));
                            value.push_back(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::UNSIGNED_CHAR)
                        {
                            unsigned char returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned char, returnValue));
                            value.push_back(returnValue);
                        }                                                
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::SHORT)
                        {
                            short returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(short, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::UNSIGNED_SHORT)
                        {
                            unsigned short returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned short, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::INT)
                        {
                            int returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(int, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::UNSIGNED_INT)
                        {
                            unsigned int returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned int, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::LONG)
                        {
                            long returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(long, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::UNSIGNED_LONG)
                        {
                            unsigned long returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned long, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::LONG_LONG)
                        {
                            long long returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(long long, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::UNSIGNED_LONG_LONG)
                        {
                            unsigned long long returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned long long, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::FLOAT)
                        {
                            float returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(float, returnValue));
                            value = QString::number(returnValue);
                        }
                        else if(methodReturnType == CSTL::SUPPORTED_TYPES::DOUBLE)
                        {
                            double returnValue;
                            ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(double, returnValue));
                            value = QString::number(returnValue);
                        }

                        if(!ok)
                        {
                            outPutText += "***ERROR - METHOD " + prop.m_method + " .***";
                        }
                        else
                        {
                            outPutText += value;
                        }
                    }
                    else
                    {
                        outPutText += "***ERROR - METHOD NOT FOUND " + prop.m_method + " .***";
                    }
                }
                expr.clear();
                continue;
            }
        }
        if(start)
        {
            expr.push_back(ch);
        }
        else
        {
            outPutText.push_back(ch);
        }
    }
}

QMap<QString, QString> CSTLCompilerAttributes::getAttributes(const QXmlStreamAttributes &attributes)
{
    QMap<QString, QString> attr;
    for(int i = 0; i < attributes.size(); ++i)
    {
        QString name(attributes[i].name().toString());
        QString value(attributes[i].value().toString());
        attr.insert(name, value);
    }
    return attr;
}

CWF_END_NAMESPACE

/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "metaclassparser.h"

CWF_BEGIN_NAMESPACE

MetaClassParser::MetaClassParser(QObject *object)
{
    const QMetaObject *meta = object->metaObject();
    int total = meta->propertyCount();
    for(int i = 0; i < total; ++i)
    {
        QMetaProperty prop(meta->property(i));
        QString propertyType(prop.typeName());
        QString propertyName(prop.name());
        properties.insert(propertyType + " " + propertyName, prop);
    }

    total = meta->methodCount();
    for(int i = 0; i < total; ++i)
    {
        QMetaMethod method(meta->method(i));
        QString returnType(method.typeName());
        QString xxx = method.methodSignature();
        std::tuple<QString, QString> signature(returnType, method.methodSignature());
        methods.insert(signature, method);
    }
}

QString MetaClassParser::getReturnType(const QString &methodName)
{
    for(QMap<std::tuple<QString, QString>, QMetaMethod>::iterator it = methods.begin();
        it != methods.end(); ++it)
    {
        QString name = std::get<1>(it.key());
        if(name == methodName)
        {
            return std::get<0>(it.key());
        }
    }
    return "";
}

QString MetaClassParser::getParameterType(const QString &methodName)
{
    for(QMap<std::tuple<QString, QString>, QMetaMethod>::iterator it = methods.begin();
        it != methods.end(); ++it)
    {
        QString name = std::get<1>(it.key());
        if(name.startsWith(methodName + "("))
        {
            return it.value().methodSignature().replace(methodName, "").replace("(", "").replace(")", "");
        }
    }
    return "";
}

void *MetaClassParser::instantiateClassByName(const QByteArray &name)
{
    int id = QMetaType::type(name);
    if (id != 0)
        return QMetaType::create(id);
    return nullptr;
}

CWF_END_NAMESPACE

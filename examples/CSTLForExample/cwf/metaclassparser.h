/**
  @file metaclassparser.h
  @author Herik Lima
*/

#ifndef METACLASSPARSER_H
#define METACLASSPARSER_H

#include <QMap>
#include <tuple>
#include <QDebug>
#include <QString>
#include <QObject>
#include <iostream>
#include <QMetaType>
#include <QMetaMethod>
#include <QMetaProperty>


namespace CWF
{
    class MetaClassParser
    {
    public:
        QMap<std::tuple<QString, QString>, QMetaMethod> methods;
        QMap<QString, QMetaProperty> properties;
        explicit MetaClassParser(QObject *object);
        QString getReturnType(const QString &methodName);
        QString getParameterType(const QString &methodName);
        static void *instantiateClassByName(const QByteArray &name);
    };
}

#endif // METACLASSPARSER_H

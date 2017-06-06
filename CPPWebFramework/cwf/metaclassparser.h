/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
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
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief This class extracts all information from a QObject.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT MetaClassParser
{
public:
    QMap<std::tuple<QString, QString>, QMetaMethod> methods;
    QMap<QString, QMetaProperty> properties;
    /**
     * @brief Extracts all properties and methods names from a QObject.
     * @param QObject *object : Object.
     */
    explicit MetaClassParser(QObject *object);
    /**
     * @brief Returns the method return type given a method name.
     * @param const QString &methodName : Method name.
     * @return QString : Return type.
     */
    QString getReturnType(const QString &methodName);
    /**
     * @brief Returns the method parameter type given a method name.
     * @param const QString &methodName : Method name.
     * @return QString : Parameter type.
     */
    QString getParameterType(const QString &methodName);
    /**
     * @brief Instantiate a class by name.
     * @param const QByteArray &name : Class name.
     * @return void * : Returns nullptr if fails.
     */
    static void *instantiateClassByName(const QByteArray &name);
};

CWF_END_NAMESPACE

#endif // METACLASSPARSER_H

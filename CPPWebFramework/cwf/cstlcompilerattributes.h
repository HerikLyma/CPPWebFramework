/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CSTLCOMPILERATTRIBUTES_H
#define CSTLCOMPILERATTRIBUTES_H

#include <QMap>
#include <QString>
#include <QObject>
#include <QXmlStreamAttributes>
#include "properties.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
* @brief This class search for expressions #{obj.get} and compiles it.
*/
class CPPWEBFRAMEWORKSHARED_EXPORT CSTLCompilerAttributes
{
    QMap<QString, QObject *> &objects;
public:
    explicit CSTLCompilerAttributes(QMap<QString, QObject *> &objects);
    QString buildAttributes(QMap<QString, QString> &attr, bool keyValue = true);
    void compileAttributes(QMap<QString, QString> &attr);
    void compile(QString &text, QString &outPutText);
    QMap<QString, QString> getAttributes(const QXmlStreamAttributes &attributes);
};

CWF_END_NAMESPACE

#endif // CSTLCOMPILERATTRIBUTES_H

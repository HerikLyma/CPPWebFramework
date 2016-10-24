/**
  @file cstlcompilerattributes.h
  @author Herik Lima
*/

#ifndef CSTLCOMPILERATTRIBUTES_H
#define CSTLCOMPILERATTRIBUTES_H

#include <QMap>
#include <QString>
#include <QObject>
#include <QXmlStreamAttributes>
#include "properties.h"

namespace CWF
{
   /**
    * @brief This class search for expressions #{obj.get} and compiles it.
    */
    class CSTLCompilerAttributes
    {
        QMap<QString, QObject *> &objects;
    public:
        CSTLCompilerAttributes(QMap<QString, QObject *> &objects);
        QString buildAttributes(QMap<QString, QString> &attr, bool keyValue = true);
        void compileAttributes(QMap<QString, QString> &attr);
        void compile(QString &text, QString &outPutText);
        QMap<QString, QString> getAttributes(const QXmlStreamAttributes &attributes);
    };
}

#endif // CSTLCOMPILERATTRIBUTES_H

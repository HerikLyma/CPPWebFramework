/**
  @file cstlcompiler.h
  @author Herik Lima
*/

#ifndef CSTLCOMPILER_H
#define CSTLCOMPILER_H

#include <QMap>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStringList>
#include <QMetaObject>
#include <QMetaMethod>
#include <qdebug.h>
#include <vector>
#include "properties.h"
#include "forattributes.h"
#include "qlistobject.h"
#include "ifattributes.h"

namespace CWF
{
    class CSTLCompiler
    {        
        QByteArray str;
        QMap<QString, QObject *>  &objects;
        bool isStrFileName;
        QByteArray openFile(QXmlStreamReader &xml);       
        QByteArray processXml(QXmlStreamReader &xml);
        QByteArray processOutTag(QMap<QString, QString> &attr);
        QByteArray processForTag(QXmlStreamReader &xml);
        QByteArray processIfTag(QXmlStreamReader &xml);
        QByteArray getBody(QXmlStreamReader &xml, const QString &tagName);
    public:
        CSTLCompiler(const QByteArray &str, QMap<QString, QObject *> &objects, bool isStrFileName = true);
        QByteArray output();
    };
}

#endif // CSTLCOMPILER_H

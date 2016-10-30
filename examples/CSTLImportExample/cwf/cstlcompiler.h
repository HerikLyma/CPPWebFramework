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
#include "qlistobject.h"


namespace CWF
{
   /**
    * @brief This class compiles xhtml pages with CSTL (C++ Server Pages Standard Tags Library).
    */
    class CSTLCompiler
    {        
        QByteArray str;
        QMap<QString, QObject *>  &objects;
        bool isStrFileName;
        /**
         * @brief Try to open the xhtml page, if it fails, it will return an error QByteArray, else, it will return an empty QByteArray.
         * @param QXmlStreamReader &xml : The opened xml.
         * @return QByteArray : Return an error QByteArray, else, it will return an empty QByteArray.
         */
        QByteArray openFile(QXmlStreamReader &xml);               
        /**
         * @brief Process XML file to find special tags and expressions.
         * @param QXmlStreamReader &xml : The opened xml.
         * @return QByteArray : Returns the processed QByteArray or an error.
         */
        QByteArray processXml(QXmlStreamReader &xml);       
        /**
         * @brief Process out tag from CSTL
         * @param QXmlStreamReader &xml : The opened xml.
         * @return QByteArray : Returns the processed QByteArray or an error.
         */
        QByteArray processOutTag(QMap<QString, QString> &attr);        
        /**
         * @brief Process for tag from CSTL
         * @param QXmlStreamReader &xml : The opened xml.
         * @return QByteArray : Returns the processed QByteArray or an error.
         */
        QByteArray processForTag(QXmlStreamReader &xml);        
        /**
         * @brief Process if tag from CSTL
         * @param QXmlStreamReader &xml : The opened xml.
         * @return QByteArray : Returns the processed QByteArray or an error.
         */
        QByteArray processIfTag(QXmlStreamReader &xml);        
        /**
         * @brief Extract a tag body.
         * @param QXmlStreamReader &xml : The opened xml.
         * @param const QString &tagName : Tag name to extract body.
         * @return QByteArray : Tag body.
         */
        QByteArray getBody(QXmlStreamReader &xml, const QString &tagName);
    public:
        /**
         * @brief Initialize the str, objects and isStrFileName properties.
         * @param const QByteArray &str             : If isStrFileName is true, it should be a file name, else, it should be the file content.
         * @param QMap<QString, QObject *> &objects : Container objects that can be compiled into the xhtml page.
         * @param bool isStrFileName                : It indicates whether str is the name of a file or its contents.
         */
        CSTLCompiler(const QByteArray &str, QMap<QString, QObject *> &objects, bool isStrFileName = true);
        /**
         * @brief Returns the compiled xhtml page.
         * @return QByteArray : Compiled page.
         */
        QByteArray output();
    };
}

#endif // CSTLCOMPILER_H

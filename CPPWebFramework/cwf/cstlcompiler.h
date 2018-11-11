/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
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
#include "properties.h"
#include "qlistobject.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
* @brief This class compiles view pages with CSTL (C++ Server Pages Standard Tags Library).
*/
class CPPWEBFRAMEWORKSHARED_EXPORT CSTLCompiler
{
    QByteArray str;
    QString path;
    QMap<QString, QObject *>  &objects;
    bool isStrFileName;    
    bool isView = true;
    /**
     * @brief Try to open the view page, if it fails, it will return an error QByteArray, else, it will return an empty QByteArray.
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


    void processText(QString &text);
public:
    /**
     * @brief Initialize the str, objects and isStrFileName properties.
     * @param const QByteArray &str             : If isStrFileName is true, it should be a file name, else, it should be the file content.
     * @param QMap<QString, QObject *> &objects : Container objects that can be compiled into the view page.
     * @param bool isStrFileName                : It indicates whether str is the name of a file or its contents.
     */
    CSTLCompiler(const QByteArray &str, QString path, QMap<QString, QObject *> &objects, bool isStrFileName = true);
    /**
     * @brief Returns the compiled view page.
     * @return QByteArray : Compiled page.
     */
    QByteArray output();
};

CWF_END_NAMESPACE

#endif // CSTLCOMPILER_H

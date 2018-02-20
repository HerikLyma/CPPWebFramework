/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CSTLCOMPILERIMPORT_H
#define CSTLCOMPILERIMPORT_H

#include <QMap>
#include <QFile>
#include <QString>
#include <QXmlStreamAttributes>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE

/**
 * @brief Extracts and valites all attibutes from a "import" tag.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT CSTLCompilerImport
{
public:
    QMap<QString, QString> attributes;
    /**
     * @brief This constructor processes and validates the attributes of "import" tag.
     */
     CSTLCompilerImport(const QXmlStreamAttributes &attr, QString path);
};

CWF_END_NAMESPACE

#endif // CSTLCOMPILERIMPORT_H

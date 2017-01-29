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

namespace CWF
{
    class CSTLCompilerImport
    {
    public:
        QMap<QString, QString> attributes;

        explicit CSTLCompilerImport(const QXmlStreamAttributes &attr);
    };
}

#endif // CSTLCOMPILERIMPORT_H

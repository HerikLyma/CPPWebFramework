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

        CSTLCompilerImport(const QXmlStreamAttributes &attr);
    };
}

#endif // CSTLCOMPILERIMPORT_H

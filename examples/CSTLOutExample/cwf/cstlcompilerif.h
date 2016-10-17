/**
  @file cstlcompilerif.h
  @author Herik Lima
*/

#ifndef CSTLCOMPILERIF_H
#define CSTLCOMPILERIF_H

#include <QMap>
#include <QXmlStreamAttributes>

namespace CWF
{
    class CSTLCompilerIf
    {
    public:
        QMap<QString, QString> attributes;
        CSTLCompilerIf(const QXmlStreamAttributes &attr);
    };
}


#endif // CSTLCOMPILERIF_H

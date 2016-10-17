/**
  @file cstlcompilerfor.h
  @author Herik Lima
*/

#ifndef CSTLCOMPILERFOR_H
#define CSTLCOMPILERFOR_H

#include <QMap>
#include <QXmlStreamAttributes>

namespace CWF
{
    class CSTLCompilerFor
    {
    public:
        QMap<QString, QString> attributes;
        CSTLCompilerFor(const QXmlStreamAttributes &attr);
    };
}

#endif // CSTLCOMPILERFOR_H

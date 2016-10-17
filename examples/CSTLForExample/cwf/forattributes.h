/**
  @file forattributes.h
  @author Herik Lima
*/

#ifndef FORATTRIBUTE_H
#define FORATTRIBUTE_H

#include <QString>
#include <QXmlStreamAttributes>

namespace CWF
{
    /**
     * @brief The ForATTRIBUTE class is an auxiliar class to the CSTLCompiler.
     */
    class ForAttributes
    {
    public:
        QString var;
        QString items;
        QString error;
        QString from;
        QString to;
        QString increment;
        ForAttributes(const QXmlStreamAttributes &attributes);
    };
}

#endif // FORATTRIBUTE_H

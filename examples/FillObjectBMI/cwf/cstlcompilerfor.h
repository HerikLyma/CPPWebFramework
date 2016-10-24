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
    /**
     * @brief Extracts and valites all attibutes from a "for" tag.
     */
    class CSTLCompilerFor
    {
    public:
        QMap<QString, QString> attributes;
        /**
         * @brief This constructor processes and validates the attributes of "for" tags.
         * @param const QXmlStreamAttributes &attr : XML tag attributes.
         */
        CSTLCompilerFor(const QXmlStreamAttributes &attr);
    };
}

#endif // CSTLCOMPILERFOR_H

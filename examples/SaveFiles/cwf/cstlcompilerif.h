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
    /**
     * @brief Extracts and valites all attibutes from a "if" tag.
     */
    class CSTLCompilerIf
    {
    public:
        QMap<QString, QString> attributes;
        /**
         * @brief This constructor processes and validates the attributes of "if" tag.
         * @param const QXmlStreamAttributes &attr : XML tag attributes.
         */
        CSTLCompilerIf(const QXmlStreamAttributes &attr);
    };
}


#endif // CSTLCOMPILERIF_H

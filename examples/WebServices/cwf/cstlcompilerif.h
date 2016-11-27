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
    enum class RelationalOperator : char
    {
        EQUAL,
        DIFFERENT,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,
        ERROR
    };
    /**
     * @brief Extracts and valites all attibutes from a "if" tag.
     */
    class CSTLCompilerIf
    {
    public:
        RelationalOperator relationalOperator;
        bool isNumber = false;
        QMap<QString, QString> attributes;
        /**
         * @brief This constructor processes and validates the attributes of "if" tag.
         * @param const QXmlStreamAttributes &attr : XML tag attributes.
         */
        explicit CSTLCompilerIf(const QXmlStreamAttributes &attr);
    };
}


#endif // CSTLCOMPILERIF_H

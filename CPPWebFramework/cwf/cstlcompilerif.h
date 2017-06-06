/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CSTLCOMPILERIF_H
#define CSTLCOMPILERIF_H

#include <QMap>
#include <QXmlStreamAttributes>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE

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
class CPPWEBFRAMEWORKSHARED_EXPORT CSTLCompilerIf
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

CWF_END_NAMESPACE


#endif // CSTLCOMPILERIF_H

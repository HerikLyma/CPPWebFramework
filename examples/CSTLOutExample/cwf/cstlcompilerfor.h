/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
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
        explicit CSTLCompilerFor(const QXmlStreamAttributes &attr);
    };
}

#endif // CSTLCOMPILERFOR_H

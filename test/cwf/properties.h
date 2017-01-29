/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QString>
#include <QStringList>

namespace CWF
{
    /**
     * @brief The Properties class is an auxiliar class to the CSTLCompiler.
     */
    class Properties
    {
    public:
        QString m_class;
        QString m_method;
        /**
         * @brief Default constructor.
         */
        Properties() = default;
        /**
         * @brief Extracts class and method name.
         * @param const QString &classAndMethod : Class and method name.
         */
        explicit Properties(const QString &classAndMethod);
    };
}

#endif // PROPERTIES_H

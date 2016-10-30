/**
  @file properties.h
  @author Herik Lima
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
        Properties(const QString &classAndMethod);
    };
}

#endif // PROPERTIES_H

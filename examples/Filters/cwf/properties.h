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
        Properties() = default;
        Properties(const QString &classAndMethod)
        {
            QStringList temp = classAndMethod.split('.');
            if(temp.size() == 2)
            {
                m_class  = temp[0];
                m_method = temp[1];
            }
            else if(temp.size() == 1)
            {
                m_class  = temp[0];
                m_method = "getValue";
            }
        }
        QString m_class;
        QString m_method;
    };
}

#endif // PROPERTIES_H

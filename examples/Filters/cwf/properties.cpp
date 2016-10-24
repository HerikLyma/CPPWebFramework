#include "properties.h"

CWF::Properties::Properties(const QString &classAndMethod)
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

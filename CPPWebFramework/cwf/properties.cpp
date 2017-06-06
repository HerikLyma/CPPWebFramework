/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "properties.h"

CWF_BEGIN_NAMESPACE

Properties::Properties(const QString &classAndMethod)
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

CWF_END_NAMESPACE

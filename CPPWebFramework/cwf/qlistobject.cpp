/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "qlistobject.h"

CWF_BEGIN_NAMESPACE

QListObject::~QListObject()
{
    if(!autoDelete)
    {
        const QObjectList &childrenList = children();

        for(QObject *obj : childrenList)
        {
            obj->setParent(nullptr);
        }
    }
}

CWF_END_NAMESPACE

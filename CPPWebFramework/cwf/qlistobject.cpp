/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "qlistobject.h"

CWF_BEGIN_NAMESPACE

QListObject::QListObject(QObject *parent) : QObject(parent)
{

}

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

QObject *QListObject::operator [](int index) const
{
    return children()[index];
}

int QListObject::size() const
{
    return children().count();
}

void QListObject::add(QObject *object)
{
    object->setParent(this);
}

void QListObject::remove(QObject *object)
{
    object->setParent(nullptr);
}

bool QListObject::getAutoDelete() const
{
    return autoDelete;
}

void QListObject::setAutoDelete(bool value)
{
    autoDelete = value;
}

CWF_END_NAMESPACE

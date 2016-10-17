/**
  @file qlistobject.cpp
  @author Herik Lima
*/

#include "qlistobject.h"

namespace CWF
{
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
}

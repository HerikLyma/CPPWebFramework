/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef QLISTOBJECT_H
#define QLISTOBJECT_H

#include <QObject>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The QListObject class is used to pass a list of object to a xhtml page.
 * NOTE: Always when you need to pass a list of object to a xhtml page you will need to use this class,
 * your class need to inherit from the QObject class and all the methods needs to be in the public slots session.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT QListObject : public QObject
{
    Q_OBJECT
private:
    bool autoDelete = false;
public:
    /**
     * @brief This constructor can receive a parent.
     * @param QObject *parent : Parent.
     */
    explicit QListObject(QObject *parent = 0);
    /**
     * @brief
     */
    ~QListObject();
    /**
     * @brief This is an operator overload and returns a QObject given an specific index.
     * @param index : This is an integer value.
     * @return QObject *
     */
    QObject *operator [](int index) const;
    /**
     * @brief This method returns the number of elements in this QListObject.
     * @return int
     */
    int size() const;
    /**
     * @brief This method add a new QObject to the list.
     * @param QObject *object : Object.
     */
    void add(QObject *object);
    /**
     * @brief This method remove and object from the list.
     * @param o
     */
    void remove(QObject *object);
    /**
     * @brief getAutoDelete
     * @return
     */
    bool getAutoDelete() const;
    /**
     * @brief setAutoDelete
     * @param value
     */
    void setAutoDelete(bool value);
};

CWF_END_NAMESPACE

#endif // QLISTOBJECT_H

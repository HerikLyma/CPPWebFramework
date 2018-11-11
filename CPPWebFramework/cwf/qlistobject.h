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
 * @brief The QListObject class is used to pass a list of object to a view page.
 * NOTE: Always when you need to pass a list of object to a view page you will need to use this class,
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
    explicit QListObject(QObject *parent = nullptr) : QObject(parent) {}
    /**
     * @brief Contructs a QListObject with N elements.
     */
    explicit QListObject(QObject *parent, const std::initializer_list<QObject *> &objects) : QObject(parent) { add(objects); }
    /**
     * @brief Contructs a QListObject with N elements.
     */
    explicit QListObject(const std::initializer_list<QObject *> &objects) : QObject(nullptr) { add(objects); }
    /**
     * @brief Destructor.
     */
    ~QListObject();
    /**
     * @brief This is an operator overload and returns a QObject given an specific index.
     * @param index : This is an integer value.
     * @return QObject *
     */
    inline QObject *operator [](int index) const { return children()[index]; }
    /**
     * @brief This method returns the number of elements in this QListObject.
     * @return int
     */
    inline int size() const { return children().count(); }
    /**
     * @brief This method add a new QObject to the list.
     * @param QObject *object : Object.
     */
    inline void add(QObject *object) { object->setParent(this); }
    /**
     * @brief This method add a N new QObjects to the list.
     */
    inline void add(const std::initializer_list<QObject *> &objects)
    {
        std::for_each(objects.begin(), objects.end(), [&](QObject *o){ o->setParent(this); });
    }
    /**
     * @brief This method remove and object from the list.
     * @param o
     */
    inline void remove(QObject *object) { object->setParent(nullptr); }
    /**
     * @brief getAutoDelete
     * @return
     */
    inline bool getAutoDelete() const { return autoDelete; }
    /**
     * @brief setAutoDelete
     * @param value
     */
    inline void setAutoDelete(bool value) { autoDelete = value; }
};

CWF_END_NAMESPACE

#endif // QLISTOBJECT_H

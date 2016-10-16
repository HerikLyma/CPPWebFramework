/**
  @file qlistobject.h
  @author Herik Lima
*/

#ifndef QLISTOBJECT_H
#define QLISTOBJECT_H

#include <QObject>

namespace CWF
{
    /**
     * @brief The QListObject class is used to pass a list of object to a xhtml page.
     * NOTE: Always when you need to pass a list of object to a xhtml page you will need to use this class,
     * your class need to inherit from the QObject class and all the methods needs to be in the public slots session.
     */
    class QListObject : public QObject
    {
    Q_OBJECT
    private:
        bool autoDelete = false;
    public:
        /**
         * @brief This constructor can receive a parent.
         * @param parent() : This is a pointer to a QObject.
         */
        explicit QListObject(QObject *parent = 0);

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
         * @param o : This is a pointer to a QObject.
         */
        void add(QObject *object);

        /**
         * @brief This method remove
         * @param o
         */
        void remove(QObject *object);
        bool getAutoDelete() const;
        void setAutoDelete(bool value);
    };
}

#endif // QLISTOBJECT_H

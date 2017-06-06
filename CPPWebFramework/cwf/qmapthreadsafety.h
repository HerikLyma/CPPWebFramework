/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef QMAPTHREADSAFETY_H
#define QMAPTHREADSAFETY_H

#include <QMap>
#include <QPair>
#include <QMutex>
#include <QMutexLocker>
#include <atomic>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
template <typename Key, typename T>
/**
 * @brief The QMapThreadSafety class is a thread safe QMap.
 */
class QMapThreadSafety
{
    mutable QMap<Key, T> m_map;
    mutable QMutex mutex;
public:
    typedef typename QMap<Key, T>::iterator iterator;

    typedef typename QMap<Key, T>::const_iterator const_iterator;

    QMapThreadSafety() = default;

    explicit QMapThreadSafety(std::initializer_list<std::pair<Key, T>> &list) : m_map(list){}

    explicit QMapThreadSafety(const QMap<Key, T> &other) : m_map(other){}

    explicit QMapThreadSafety(const std::map<Key, T> &other) : m_map(other){}

    explicit QMapThreadSafety(QMap<Key, T> &&other) : m_map(other){}

    /**
     * @brief This method retuns the begin iterator.
     * @return iterator
     */
    iterator begin() const
    {
        QMutexLocker locker(&mutex);
        return m_map.begin();
    }

    const_iterator cbegin() const
    {
        QMutexLocker locker(&mutex);
        return m_map.cbegin();
    }

    const_iterator cend() const
    {
        QMutexLocker locker(&mutex);
        return m_map.cend();
    }

    const_iterator constBegin() const
    {
        QMutexLocker locker(&mutex);
        return m_map.constBegin();
    }

    const_iterator constEnd() const
    {
        QMutexLocker locker(&mutex);
        return m_map.constEnd();
    }

    const_iterator constFind(const Key &key) const
    {
        QMutexLocker locker(&mutex);
        return m_map.constFind(key);
    }
    /**
     * @brief This method checks if the map contains and specific element given a specific key.
     * @param key : This represents the key that you want to find.
     * @return returns true if find the key and false if not find.
     */
    bool contains(const Key &key) const
    {
        QMutexLocker locker(&mutex);
        return m_map.contains(key);
    }

    int count(const Key &key) const
    {
        QMutexLocker locker(&mutex);
        return m_map.count(key);
    }

    int count() const
    {
        QMutexLocker locker(&mutex);
        return m_map.count();
    }

    bool empty() const
    {
        QMutexLocker locker(&mutex);
        return m_map.empty();
    }
    /**
     * @brief This method retuns the end iterator.
     * @return iterator
     */
    iterator end()
    {
        QMutexLocker locker(&mutex);
        return m_map.end();
    }

    QPair<iterator, iterator> equal_range(const Key &key)
    {
        QMutexLocker locker(&mutex);
        return m_map.equal_range(key);
    }

    iterator erase(iterator pos)
    {
        QMutexLocker locker(&mutex);
        return m_map.erase(pos);
    }

    iterator find(const Key &key)
    {
        QMutexLocker locker(&mutex);
        return m_map.find(key);
    }

    const_iterator find(const Key &key) const
    {
        QMutexLocker locker(&mutex);
        return m_map.find(key);
    }

    T & first()
    {
        QMutexLocker locker(&mutex);
        return m_map.first();
    }

    const T & first() const
    {
        QMutexLocker locker(&mutex);
        return m_map.first();
    }

    const Key & firstKey() const
    {
        QMutexLocker locker(&mutex);
        return m_map.firstKey();
    }

    /**
     * @brief This method inserts a new key and value in the map.
     * @param key   : This represents the key that will be insert.
     * @param value : This represents the value that will be insert.
     */
    iterator insert(const Key &key, const T &value)
    {
        QMutexLocker locker(&mutex);
        return m_map.insert(key, value);
    }

    iterator insert(const_iterator pos, const Key &key, const T &value)
    {
        QMutexLocker locker(&mutex);
        return m_map.insert(pos, key, value);
    }

    iterator insertMulti(const Key &key, const T &value)
    {
        QMutexLocker locker(&mutex);
        return m_map.insertMulti(key, value);
    }

    bool isEmpty() const
    {
        QMutexLocker locker(&mutex);
        return m_map.isEmpty();
    }

    QList<Key> keys() const
    {
        QMutexLocker locker(&mutex);
        return m_map.keys();
    }

    QList<Key> keys(const T &value) const
    {
        QMutexLocker locker(&mutex);
        return m_map.keys();
    }

    T &last()
    {
        QMutexLocker locker(&mutex);
        return m_map.last();
    }

    const T &last() const
    {
        QMutexLocker locker(&mutex);
        return m_map.last();
    }


    iterator lowerBound(const Key &key)
    {
        QMutexLocker locker(&mutex);
        return m_map.lowerBound(key);
    }

    const_iterator lowerBound(const Key &key) const
    {
        QMutexLocker locker(&mutex);
        return m_map.lowerBound(key);
    }
    /**
     * @brief This method removes a specific element given a specific key.
     * @param key   : This represents the key that will be insert.
     * @return int
     */
    int remove(const Key &key)
    {
        QMutexLocker locker(&mutex);
        return m_map.remove(key);
    }

    int size() const
    {
        QMutexLocker locker(&mutex);
        return m_map.size();
    }

    void swap(QMap<Key, T> & other)
    {
        QMutexLocker locker(&mutex);
        m_map.swap(other);
    }

    T take(const Key &key)
    {
        QMutexLocker locker(&mutex);
        return m_map.take(key);
    }

    std::map<Key, T> toStdMap() const
    {
        QMutexLocker locker(&mutex);
        return m_map.toStdMap();
    }

    QList<Key> uniqueKeys() const
    {
        QMutexLocker locker(&mutex);
        return m_map.uniqueKeys();
    }

    QMap<Key, T> &unite(const QMap<Key, T> & other)
    {
        QMutexLocker locker(&mutex);
        return m_map.unite(other);
    }

    iterator upperBound(const Key & key)
    {
        QMutexLocker locker(&mutex);
        return m_map.upperBound(key);
    }

    const_iterator upperBound(const Key & key) const
    {
        QMutexLocker locker(&mutex);
        return m_map.upperBound(key);
    }

    const T value(const Key & key, const T & defaultValue = T()) const
    {
        QMutexLocker locker(&mutex);
        return m_map.value(key, defaultValue);
    }

    QList<T> values() const
    {
        QMutexLocker locker(&mutex);
        return m_map.values();
    }

    QList<T> values(const Key & key) const
    {
        QMutexLocker locker(&mutex);
        return m_map.values(key);
    }

    bool operator!=(const QMap<Key, T> & other) const
    {
        QMutexLocker locker(&mutex);
        return m_map.operator !=(other);
    }

    QMap<Key, T> & operator=(const QMap<Key, T> & other)
    {
        QMutexLocker locker(&mutex);
        return m_map.operator =(other);
    }

    QMap<Key, T> & operator=(QMap<Key, T> && other)
    {
        QMutexLocker locker(&mutex);
        return m_map.operator =(other);
    }

    bool operator==(const QMap<Key, T> & other) const
    {
        QMutexLocker locker(&mutex);
        return m_map.operator ==(other);
    }

    T &	operator[](const Key & key)
    {
        QMutexLocker locker(&mutex);
        return m_map.operator [](key);
    }

    /**
     * @brief This method is an overload of the operator [] and returns a value given a specific key.
     * @param key : This represents the key that you want to find.
     * @return T
     */
    const T operator [](const Key &key) const
    {
        QMutexLocker locker(&mutex);
        return m_map.operator [](key);
    }
};

CWF_END_NAMESPACE

#endif // QMAPTHREADSAFETY_H

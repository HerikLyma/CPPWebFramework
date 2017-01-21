/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
private:
    int id;
    char gender;
    QString name;
    QString address;
public:
    explicit User(QObject *parent = 0);                       
public slots:
    int getId() const;
    void setId(int value);
    char getGender() const;
    void setGender(char value);
    QString getName() const;
    void setName(const QString &value);
    QString getAddress() const;
    void setAddress(const QString &value);
};

#endif // USER_H

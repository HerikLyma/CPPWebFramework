/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "user.h"

User::User(QObject *parent) : QObject(parent), id(0)
{

}

int User::getId() const
{
    return id;
}

void User::setId(int value)
{
    id = value;
}

char User::getGender() const
{
    return gender;
}

void User::setGender(char value)
{
    gender = value;
}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &value)
{
    name = value.toUtf8();   
}

QString User::getAddress() const
{
    return address;
}

void User::setAddress(const QString &value)
{
    address = value;
}

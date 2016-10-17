/**
  @file user.cpp
  @author Herik Lima
*/

#include "user.h"

User::User(QObject *parent) : QObject(parent)
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
    name = value;
}

QString User::getAddress() const
{
    return address;
}

void User::setAddress(const QString &value)
{
    address = value;
}

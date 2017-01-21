/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &value)
{
    name = value;
}

QString User::getCategory() const
{
    return category;
}

double User::getMass() const
{
    return mass;
}

void User::setMass(double value)
{
    mass = value;
}

double User::getHeight() const
{
    return height;
}

void User::setHeight(double value)
{
    height = value;
}

double User::getBmi()
{
    bmi = height != 0 ? mass / (height * height) : 0;

    if(bmi <= 15)
    {
        category = "Very severely underweight";
    }
    else if(bmi > 15 && bmi <= 16)
    {
        category = "Severely underweight";
    }
    else if(bmi > 16 && bmi <= 18.5)
    {
        category = "Underweight";
    }
    else if(bmi > 18.5 && bmi <= 25)
    {
        category = "Normal (healthy weight)";
    }
    else if(bmi > 25 && bmi <= 30)
    {
        category = "Overweight";
    }
    else if(bmi > 30 && bmi <= 35)
    {
        category = "Obese Class I (Moderately obese)";
    }
    else if(bmi > 35 && bmi <= 40)
    {
        category = "Obese Class II (Severely obese)";
    }
    else
    {
        category = "Obese Class III (Very severely obese)";
    }

    return bmi;
}

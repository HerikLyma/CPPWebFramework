/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User : public QObject
{
    Q_OBJECT
private:
    QString name;
    QString category;
    double mass = 0;
    double height = 0;
    double bmi = 0;
public:
    explicit User(QObject *parent = 0);                        
public slots:
    QString getName() const;
    QString getCategory() const;
    void setName(const QString &value);
    double getMass() const;
    void setMass(double value);
    double getHeight() const;
    void setHeight(double value);
    double getBmi();
};

#endif // USER_H

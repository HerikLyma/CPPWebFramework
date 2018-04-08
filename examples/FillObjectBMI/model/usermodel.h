/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <QString>

class UserModel : public QObject
{
    Q_OBJECT
private:
    QString name;
    QString category;
    double mass = 0;
    double height = 0;
    double bmi = 0;
public:
    explicit UserModel(QObject *parent = 0);
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

#endif // USERMODEL_H

#ifndef USERMODEL_H
#define USERMODEL_H

#include <cwf/model.h>

class UserModel : public CWF::Model
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString phone READ getPhone WRITE setPhone)
    Q_PROPERTY(QString country READ getCountry WRITE setCountry)
    Q_PROPERTY(QString state READ getState WRITE setState)
    QString name;
    QString phone;
    QString country;
    QString state;
public:
    explicit UserModel(CWF::SqlDatabaseStorage &connection) : CWF::Model(connection, "usuario")
    {
    }
public slots:
    QString getName() const { return name; }

    void setName(const QString &value) { name = value; }

    QString getPhone() const { return phone; }

    void setPhone(const QString &value) { phone = value; }

    QString getCountry() const { return country; }

    void setCountry(const QString &value) { country = value; }

    QString getState() const { return state; }

    void setState(const QString &value) { state = value; }
};

#endif // USERMODEL_H

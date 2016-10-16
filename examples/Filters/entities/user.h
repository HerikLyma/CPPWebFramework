#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
private:
    QString name;
    QString password;
public:
    explicit User(QObject *parent = 0);    
public slots:
    QString getName() const;
    void setName(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);
};

#endif // USER_H

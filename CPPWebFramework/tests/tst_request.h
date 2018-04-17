#ifndef TST_HTTPSERVLETREQUEST_H
#define TST_HTTPSERVLETREQUEST_H

#include <QtTest>
#include <cwf/request.h>

class ClientTest : public QObject
{
    Q_OBJECT

    QString a;
public slots:
    QString getA() const { return a; }

    void setA(const QString &value) { a = value; }
};


class TST_Request : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_HTTPSERVLETREQUEST_H

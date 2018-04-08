#ifndef TST_HTTPSERVLETREQUEST_H
#define TST_HTTPSERVLETREQUEST_H

#include <QtTest>
#include <cwf/request.h>

class TST_Request : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_HTTPSERVLETREQUEST_H

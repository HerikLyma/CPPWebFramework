#ifndef TST_HTTPSERVLETREQUEST_H
#define TST_HTTPSERVLETREQUEST_H

#include <QtTest>
#include <cwf/httpservletrequest.h>

class TST_HttpServletRequest : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_HTTPSERVLETREQUEST_H

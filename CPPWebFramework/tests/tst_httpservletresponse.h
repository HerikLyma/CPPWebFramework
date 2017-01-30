#ifndef TST_HTTPSERVLETRESPONSE_H
#define TST_HTTPSERVLETRESPONSE_H

#include <QtTest>
#include <cwf/httpservletresponse.h>

class TST_HttpServletResponse : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_HTTPSERVLETRESPONSE_H

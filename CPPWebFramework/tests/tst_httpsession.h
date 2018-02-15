#ifndef TST_HTTPSESSION_H
#define TST_HTTPSESSION_H

#include <QtTest>
#include <cwf/httpsession.h>

class TST_HttpSession : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_HTTPSESSION_H

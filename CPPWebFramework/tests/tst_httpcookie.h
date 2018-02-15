#ifndef TST_HTTPCOOKIE_H
#define TST_HTTPCOOKIE_H

#include <QtTest>
#include <cwf/httpcookie.h>

class TST_HttpCookie : public QObject
{
    Q_OBJECT
private slots:
    void test();
private:
    CWF::HttpCookie manual();

    CWF::HttpCookie automatic();
};

#endif // TST_HTTPCOOKIE_H

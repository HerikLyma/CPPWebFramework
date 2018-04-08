#ifndef TST_CPPWEBSERVLET_H
#define TST_CPPWEBSERVLET_H

#include <QtTest>
#include <cwf/cppwebcontroller.h>

class TST_CppWebController : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_CPPWEBSERVLET_H

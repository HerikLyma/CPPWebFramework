#ifndef TST_REQUESTDISPATCHER_H
#define TST_REQUESTDISPATCHER_H

#include <QtTest>
#include <cwf/requestdispatcher.h>

class TST_RequestDispatcher : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_REQUESTDISPATCHER_H

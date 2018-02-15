#ifndef TST_QMAPTHREADSAFETY_H
#define TST_QMAPTHREADSAFETY_H

#include <QtTest>
#include <cwf/qmapthreadsafety.h>

class TST_QMapThreadSafety : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_QMAPTHREADSAFETY_H

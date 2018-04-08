#ifndef TST_CONFIGURATION_H
#define TST_CONFIGURATION_H

#include <QDir>
#include <QFile>
#include <QtTest>
#include <cwf/configuration.h>

class TST_Configuration : public QObject
{
    Q_OBJECT
private slots:
    void test();
};   

#endif // TST_CONFIGURATION_H

#ifndef TST_HTTPPARSER_H
#define TST_HTTPPARSER_H

#include <QtTest>
#include <cwf/httpparser.h>

class TST_HttpParser : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_HTTPPARSER_H

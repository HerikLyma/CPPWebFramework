#ifndef TST_HTTPPARSER_H
#define TST_HTTPPARSER_H

#include <QtTest>
#include <cwf/httpparser.h>

class TST_HttpParser : public QObject
{
    Q_OBJECT
private slots:
    void test();

    void testGet();

    void testPost();

    QByteArray buildGetRequest();

    QByteArray buildPostRequest();
};

#endif // TST_HTTPPARSER_H

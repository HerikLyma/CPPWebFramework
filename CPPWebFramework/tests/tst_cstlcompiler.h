#ifndef TST_CSTLCOMPILER_H
#define TST_CSTLCOMPILER_H

#include <QtTest>
#include <tests/tst_request.h>
#include <cwf/cstlcompiler.h>

enum class NUMBER_ATTR : char
{
    ZERO,
    TWO,
    THREE
};

class TST_CSTLCompiler : public QObject
{
    Q_OBJECT
    const QByteArray header = "<head><title>TestHeader</title></head>";
private slots:
    void test();

    void testImport();

    void testForOutIf();

    void fillClient(ClientTest &client, short h);

    QByteArray buildHtmlForIf(const QByteArray &condition, NUMBER_ATTR number = NUMBER_ATTR::TWO);

    void createFile(const QString &name, const QByteArray &content);
};

#endif // TST_CSTLCOMPILER_H

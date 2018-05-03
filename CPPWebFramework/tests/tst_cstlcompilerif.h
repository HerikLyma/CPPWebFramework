#ifndef TST_CSTLCOMPILERIF_H
#define TST_CSTLCOMPILERIF_H

#include <QtTest>
#include <cwf/cstlcompilerif.h>

class TST_CSTLCompilerIf : public QObject
{
    Q_OBJECT
private slots:
    void test();

    QByteArray buildHtml();
};

#endif // TST_CSTLCOMPILERIF_H

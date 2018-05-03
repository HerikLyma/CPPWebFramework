#ifndef TST_CSTLCOMPILEROUT_H
#define TST_CSTLCOMPILEROUT_H

#include <QtTest>

class TST_CSTLCompilerOut : public QObject
{
    Q_OBJECT
private slots:
    void test();

    QByteArray buildHtml();
};

#endif // TST_CSTLCOMPILEROUT_H

#include "tst_cstlcompiler.h"
#include <QFile>

void TST_CSTLCompiler::test()
{
    testImport();
}

void TST_CSTLCompiler::testImport()
{
    QMap<QString, QObject *> objects;
    createFile("header.html", header);
    QByteArray html;
    html  = "<html>";
    html += "<body>";
    html += "<import url=\"/header.html\"/>";
    html += "</body>";
    html += "</html>";
    createFile("home.html", html);

    QVERIFY2(CWF::CSTLCompiler(html, QDir().currentPath(), objects, false).output().contains("TestHeader"), "Should contains 'TestHeader'");
    QVERIFY2(!CWF::CSTLCompiler(html, "xxx", objects, false).output().contains("TestHeader"), "Should not contains 'TestHeader'");
    QVERIFY2(CWF::CSTLCompiler((QDir().currentPath() + "/home.html").toLatin1(), QDir().currentPath(), objects).output().contains("import url"), "Should contains 'import url'");
}

void TST_CSTLCompiler::createFile(const QString &name, const QByteArray &content)
{
    QFile file(name);
    QVERIFY2(file.open(QIODevice::WriteOnly), ("Could not create " + name).toStdString().data());
    file.write(content);
}

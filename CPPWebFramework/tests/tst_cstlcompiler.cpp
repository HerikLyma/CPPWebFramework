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
    QByteArray originalHtml;
    originalHtml  = "<html>";
    originalHtml += "<body>";
    originalHtml += "xxx";
    originalHtml += "</body>";
    originalHtml += "</html>";

    QByteArray copy1(originalHtml);
    QByteArray copy2(originalHtml);
    QByteArray copy3(originalHtml);
    QByteArray copy4(originalHtml);

    copy1.replace("xxx", "<import url=\"/header.html\"/>");
    copy2.replace("xxx", "<import/>");
    copy3.replace("xxx", "<import url=\"/header.html\" url2=\"/header.html\"/>");
    copy4.replace("xxx", "<import x=\"/header.html\"/>");
    createFile("home.html", copy1);

    QVERIFY2(CWF::CSTLCompiler(copy1, QDir().currentPath(), objects, false).output().contains("TestHeader"), "Should contains 'TestHeader'");
    QVERIFY2(!CWF::CSTLCompiler(copy1, "xxx", objects, false).output().contains("TestHeader"), "Should not contains 'TestHeader'");
    QVERIFY2(CWF::CSTLCompiler((QDir().currentPath() + "/home.html").toLatin1(), QDir().currentPath(), objects).output().contains("import url"), "Should contains 'import url'");
    QVERIFY2(CWF::CSTLCompiler(copy2, QDir().currentPath(), objects, false).output().contains("NEEDS THE URL"), "Should contains 'NEEDS THE URL'");
    QVERIFY2(CWF::CSTLCompiler(copy3, QDir().currentPath(), objects, false).output().contains("ONLY NEEDS"), "Should contains 'ONLY NEEDS'");
    QVERIFY2(CWF::CSTLCompiler(copy4, QDir().currentPath(), objects, false).output().contains("NEEDS THE URL"), "Should contains 'NEEDS THE URL'");
}

void TST_CSTLCompiler::createFile(const QString &name, const QByteArray &content)
{
    QFile file(name);
    QVERIFY2(file.open(QIODevice::WriteOnly), ("Could not create " + name).toStdString().data());
    file.write(content);
}

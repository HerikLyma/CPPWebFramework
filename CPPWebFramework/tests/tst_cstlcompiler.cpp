#include "tst_cstlcompiler.h"
#include <QFile>

void TST_CSTLCompiler::test()
{
    testImport();
    testForOutIf();
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

void TST_CSTLCompiler::testForOutIf()
{
    ClientTest a, b;
    fillClient(a, 0);
    fillClient(b, 1);

    CWF::QListObject obj;
    obj.add(&a);
    obj.add(&b);

    QMap<QString, QObject *> objects({{"clients", &obj}});

    QByteArray equal(buildHtmlForIf("equal"));
    QByteArray different(buildHtmlForIf("different"));
    QByteArray greater(buildHtmlForIf("greater"));
    QByteArray greaterEqual(buildHtmlForIf("greater_equal"));
    QByteArray lessEqual(buildHtmlForIf("less_equal"));

    QVERIFY2(CWF::CSTLCompiler(equal, QDir().currentPath(), objects, false).output().contains("ab1DE111111111.51.5"), "Should contains 'ab1DE111111111.51.5'");
    QVERIFY2(CWF::CSTLCompiler(different, QDir().currentPath(), objects, false).output().contains("ab1DE011111111.51.5"), "Should contains 'ab1DE011111111.51.5'");
    QVERIFY2(!CWF::CSTLCompiler(greater, QDir().currentPath(), objects, false).output().contains("ab1DE"), "Should not contains 'ab1DE'");
    QVERIFY2(CWF::CSTLCompiler(greaterEqual, QDir().currentPath(), objects, false).output().contains("ab1DE111111111.51.5"), "Should contains 'ab1DE111111111.51.5'");
    QVERIFY2(CWF::CSTLCompiler(lessEqual, QDir().currentPath(), objects, false).output().contains("ab1DE111111111.51.5"), "Should contains 'ab1DE111111111.51.5'");
}

void TST_CSTLCompiler::fillClient(ClientTest &client, short h)
{
    client.setA("a");
    client.setB("b");
    client.setC(true);
    client.setD('D');
    client.setE('E');
    client.setH(h);
    client.setI(1);
    client.setJ(1);
    client.setK(1);
    client.setL(1);
    client.setM(1);
    client.setN(1);
    client.setO(1);
    client.setP(1.5);
    client.setQ(1.5);
}

QByteArray TST_CSTLCompiler::buildHtmlForIf(const QByteArray &condition)
{
    QByteArray html;
    html  = "<html>";
    html +=     "<body>";
    html +=         "<for items=\"clients\" var=\"client\">";
    html +=             "<if var=\"#{client.getH}\" " + condition + "=\"1\">";
    html +=                 "<center>";
    html +=                     "<out value=\"#{client.getA}\"/>";
    html +=                     "<out value=\"#{client.getB}\"/>";
    html +=                     "<out value=\"#{client.getC}\"/>";
    html +=                     "<out value=\"#{client.getD}\"/>";
    html +=                     "<out value=\"#{client.getE}\"/>";
    html +=                     "<out value=\"#{client.getH}\"/>";
    html +=                     "<out value=\"#{client.getI}\"/>";
    html +=                     "<out value=\"#{client.getJ}\"/>";
    html +=                     "<out value=\"#{client.getK}\"/>";
    html +=                     "<out value=\"#{client.getL}\"/>";
    html +=                     "<out value=\"#{client.getM}\"/>";
    html +=                     "<out value=\"#{client.getN}\"/>";
    html +=                     "<out value=\"#{client.getO}\"/>";
    html +=                     "<out value=\"#{client.getP}\"/>";
    html +=                     "<out value=\"#{client.getQ}\"/>";
    html +=                 "</center>";
    html +=             "</if>";
    html +=         "</for>";
    html +=     "</body>";
    html += "</html>";

    return html;
}

void TST_CSTLCompiler::createFile(const QString &name, const QByteArray &content)
{
    QFile file(name);
    QVERIFY2(file.open(QIODevice::WriteOnly), ("Could not create " + name).toStdString().data());
    file.write(content);
}

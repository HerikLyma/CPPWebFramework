#include "tst_cstlcompilerif.h"
#include <cwf/cstlcompiler.h>
#include <cwf/variant.h>

void TST_CSTLCompilerIf::test()
{
    {
        CWF::Variant var(1);
        QMap<QString, QObject *> objects({{"var", &var}});
        QByteArray r = CWF::CSTLCompiler(buildHtml(), QDir().currentPath(), objects, false).output();
        QVERIFY2(r.contains("One"), "Should contains 'One'");
        QVERIFY2(r.contains("Greater than Zero"), "Should contains 'Greater than Zero'");
        QVERIFY2(r.contains("Less Two"), "Should contains 'Less Two'");
        QVERIFY2(r.contains("Less equal Two"), "Should contains 'Less equal Two'");
        QVERIFY2(r.contains("Greater equal One"), "Should contains 'Greater equal One'");
        QVERIFY2(!r.contains("Test"), "Should not contains 'Test'");
    }
}

QByteArray TST_CSTLCompilerIf::buildHtml()
{
    QByteArray html;
    html  = "<html>";
    html +=     "<body>";
    html +=         "<if var=\"#{var.toInt}\" equal=\"2\">";
    html +=             "Test";
    html +=         "</if>";
    html +=         "<if var=\"#{var.toInt}\" equal=\"1\">";
    html +=             "One";
    html +=             "<if var=\"#{var.toInt}\" greater=\"0\">";
    html +=                 "Greater than Zero";
    html +=             "</if>";
    html +=         "</if>";
    html +=         "<if var=\"#{var.toInt}\" less=\"2\">";
    html +=             "<if var=\"#{var.toInt}\" less_equal=\"2\">";
    html +=                 "<if var=\"#{var.toInt}\" greater_equal=\"1\">";
    html +=                     "Greater equal One";
    html +=                 "</if>";
    html +=                 "Less equal Two";
    html +=             "</if>";
    html +=             "Less Two";
    html +=         "</if>";
    html +=     "</body>";
    html += "</html>";

    return html;
}

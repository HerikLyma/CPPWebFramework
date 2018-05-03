#include "tst_cstlcompilerout.h"
#include <cwf/cstlcompiler.h>
#include <cwf/variant.h>

void TST_CSTLCompilerOut::test()
{
    {
        CWF::Variant var(1);
        QMap<QString, QObject *> objects({{"var", &var}});
        QByteArray r = CWF::CSTLCompiler(buildHtml(), QDir().currentPath(), objects, false).output();
        QVERIFY2(r.contains("1"), "Should contains '1'");
    }
}

QByteArray TST_CSTLCompilerOut::buildHtml()
{
    QByteArray html;
    html  = "<html>";
    html +=     "<body>";
    html +=         "Um #{var.toInt} + #{var.toInt} = 2";
    html +=         "<a link=\"#{var.toInt} #{var.toInt} \"/>";
    html +=     "</body>";
    html += "</html>";

    return html;
}

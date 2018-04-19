#include "tst_session.h"
#include <cwf/variant.h>

void TST_Session::test()
{
    CWF::Session session("1", 1);
    session.setSessionTimeOut(1);
    session.setAutoClearAttributes(true);
    session.addAttribute("a", new CWF::Variant(0));
    session.addAttribute("b", new CWF::Variant(1));
    session.validate();
    QThread::msleep(10);
    QVERIFY2(session.getId() == "1", "Should be 1");
    QVERIFY2(session.getSessionTimeOut() == 1, "Should be 1");
    QVERIFY2(session.getAttributeNames().size() == 2, "Should be 2");
    QVERIFY2(session.isExpired(), "Should be true");
    QVERIFY(session.getLastAccessedTime() <= QDateTime::currentMSecsSinceEpoch());

}

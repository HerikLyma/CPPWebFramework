#include "tst_qlistobject.h"

void TST_QListObject::test()
{
    CWF::QListObject listObj;

    listObj.add(new QObject);
    listObj.add(new QObject);

    QVERIFY2(listObj.size() == 2, "Should be equal 2");
    QObject *obj = listObj[0];
    QVERIFY2(obj != nullptr, "Should be different nullptr");
    listObj.remove(obj);
    QVERIFY2(listObj.size() == 1, "Should be equal 1");
    listObj.setAutoDelete(false);
    QVERIFY2(listObj.getAutoDelete() == false, "Should be equal false");
}

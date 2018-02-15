#include "tst_qmapthreadsafety.h"

void TST_QMapThreadSafety::test()
{
    CWF::QMapThreadSafety<int, QString> myMap;
    QVERIFY2(myMap.insert(1, "First").key() == 1, "Should return 1");
    QVERIFY2(myMap.insert(2, "Second").key() == 2, "Should return 2");
    QVERIFY2(myMap.size() == 2, "Should return 2");
    QVERIFY2(myMap.contains(1) == true, "Should return true");
    QVERIFY2(myMap.remove(1) > 0, "Should return > 0");
    QVERIFY2(myMap.size() == 1, "Should return 1");
    QVERIFY2(myMap.contains(1) == false, "Should return false");
}

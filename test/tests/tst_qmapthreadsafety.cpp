#include "tst_qmapthreadsafety.h"

void TST_QMapThreadSafety::test()
{
    CWF::QMapThreadSafety<int, QString> myMap;
    myMap.insert(1, "First");
    myMap.insert(2, "Second");
    QVERIFY2(myMap.size() == 2, "Should return 2");
    QVERIFY2(myMap.contains(1) == true, "Should return true");
    myMap.remove(1);
    QVERIFY2(myMap.size() == 1, "Should return 1");
    QVERIFY2(myMap.contains(1) == false, "Should return false");
}

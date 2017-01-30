#include "tst_httprequestmethod.h"


void TST_HttpRequestMethod::test()
{
    QVERIFY2(CWF::HttpRequestMethod::getDelete()  == "DELETE" , "Shoud be equal DELETE");
    QVERIFY2(CWF::HttpRequestMethod::getGet()     == "GET"    , "Shoud be equal GET");
    QVERIFY2(CWF::HttpRequestMethod::getHead()    == "HEAD"   , "Shoud be equal HEAD");
    QVERIFY2(CWF::HttpRequestMethod::getOptions() == "OPTIONS", "Shoud be equal OPTIONS");
    QVERIFY2(CWF::HttpRequestMethod::getPost()    == "POST"   , "Shoud be equal POST");
    QVERIFY2(CWF::HttpRequestMethod::getPut()     == "PUT"    , "Shoud be equal PUT");
    QVERIFY2(CWF::HttpRequestMethod::getTrace()   == "TRACE"  , "Shoud be equal TRACE");
}

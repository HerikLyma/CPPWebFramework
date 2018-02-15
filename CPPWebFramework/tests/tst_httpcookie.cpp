#include "tst_httpcookie.h"
#include <QBitArray>

void TST_HttpCookie::test()
{
    QVector<CWF::HttpCookie> cookies;
    cookies.push_back(manual());
    cookies.push_back(automatic());

    for(CWF::HttpCookie &cookie : cookies)
    {
        QVERIFY2(cookie.getComment() == "test", "Should be test");
        QVERIFY2(cookie.getDomain() == "www.test.com.xyz", "Should be www.test.com.xyz");
        QVERIFY2(cookie.getMaxAge() == 30, "Should return 30");        
        QVERIFY2(cookie.getName() == "Name", "Should be Name");
        QVERIFY2(cookie.getPath() == "/home/Test/server", "Should be /home/Test/server");
        QVERIFY2(cookie.getSecure() == true, "Should return true");
        QVERIFY2(cookie.getValue() == "Test Cookie", "Should be Test Cookie");
        QVERIFY2(cookie.getVersion() == 1, "Should be 1");
        QVERIFY2(cookie.toByteArray() == "Name=Test Cookie; Comment=test; Domain=www.test.com.xyz; Max-Age=30; Path=/home/Test/server; Secure; Version=1",
                 "Shoud be Name=Test Cookie; Comment=test; Domain=www.test.com.xyz; Max-Age=30; Path=/home/Test/server; Secure; Version=1");
    }

    CWF::HttpCookie cookie("Name", "Test Cookie");
    QVERIFY2(cookie.getName() == "Name", "Should be Name");
    QVERIFY2(cookie.getValue() == "Test Cookie", "Should be Test Cookie");
}


CWF::HttpCookie TST_HttpCookie::manual()
{
    CWF::HttpCookie cookie;

    cookie.setComment("test");
    cookie.setDomain("www.test.com.xyz");
    cookie.setMaxAge(30);
    cookie.setName("Name");
    cookie.setPath("/home/Test/server");
    cookie.setSecure(true);
    cookie.setValue("Test Cookie");

    return cookie;
}

CWF::HttpCookie TST_HttpCookie::automatic()
{
    CWF::HttpCookie cookie("Name=Test Cookie; Comment=test; Domain=www.test.com.xyz; Path=/home/Test/server; Max-Age=30; Secure=true; Version=1");
    return cookie;
}

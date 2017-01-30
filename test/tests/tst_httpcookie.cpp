#include "tst_httpcookie.h"
#include <QBitArray>

void TST_HttpCookie::test()
{
   CWF::HttpCookie cookie;


   cookie.setComment("comentario cookie teste");
   cookie.setDomain("www.test.com.xyz");
   cookie.setMaxAge(30);
   cookie.setName("Herik Lima de Castro");
   cookie.setPath("/home/Test/server");
   cookie.setSecure(true);
   cookie.setValue("Testes Cokkie");


   QVERIFY2(cookie.getComment() == "comentario cookie teste", "Should be comentario cookie teste");
   QVERIFY2(cookie.getDomain() == "www.test.com.xyz", "Should be www.test.com.xyz");
   QVERIFY2(cookie.getMaxAge() == 30, "Should return 30");
   QVERIFY2(cookie.getName() == "Herik Lima de Castro", "Should be Herik Lima de Castro");
   QVERIFY2(cookie.getPath() == "/home/Test/server", "Should be /home/Test/server");
   QVERIFY2(cookie.getSecure() == true, "Should return true");
   QVERIFY2(cookie.getValue() == "Testes Cokkie", "Should be Testes Cokkie");

}

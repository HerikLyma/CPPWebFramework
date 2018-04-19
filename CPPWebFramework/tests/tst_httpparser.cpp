#include "tst_httpparser.h"

void TST_HttpParser::test()
{
    testGet();
    testPost();
}

void TST_HttpParser::testGet()
{
    QByteArray req(buildGetRequest());
    CWF::HttpParser parser(req);

    QVERIFY2(parser.getCookies().size() == 1, "Should be 1");
    QVERIFY2(parser.getUrl() == "/home", "Should be /");
    QVERIFY2(parser.getParameter("id").toInt() == 10, "Should be 10");
    QVERIFY2(parser.getParameter("nome") == "Herik", "Should be Herik");
    QVERIFY2(parser.getHttpVersion().endsWith("1.1"), "Should be 1.1");
    QVERIFY2(parser.getMethod() == "GET", "Should be GET");
    QVERIFY2(!parser.isMultiPart(), "Should be not be multiPart");
}

void TST_HttpParser::testPost()
{
    QByteArray req(buildPostRequest());
    CWF::HttpParser parser(req);

    QVERIFY2(parser.getCookies().size() == 1, "Should be 1");
    QVERIFY2(parser.getUrl() == "/home", "Should be /");
    QVERIFY2(parser.getParameter("id").toInt() == 10, "Should be 10");
    QVERIFY2(parser.getParameter("nome") == "Herik", "Should be Herik");
    QVERIFY2(parser.getHttpVersion().endsWith("1.1"), "Should be 1.1");
    QVERIFY2(parser.getMethod() == "POST", "Should be POST");
    QVERIFY2(!parser.isMultiPart(), "Should be not be multiPart");
}

QByteArray TST_HttpParser::buildGetRequest()
{
    QByteArray req;

    req  = "GET /home?id=10&nome=Herik HTTP/1.1\r\n";
    req += "Host: localhost:8080\r\n";
    req += "Connection: keep-alive\r\n";
    req += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n";
    req += "Cookie: uid=12345678901234567890\r\n\r\n";

    return req;
}

QByteArray TST_HttpParser::buildPostRequest()
{
    QByteArray req;

    req  = "POST /home HTTP/1.1\r\n";
    req += "Host: localhost:8080\r\n";
    req += "Connection: keep-alive\r\n";
    req += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n";
    req += "Content-Type: application/x-www-form-urlencoded\r\n";
    req += "Cookie: uid=12345678901234567890\r\n\r\n";
    req += "id=10&nome=Herik";

    return req;
}

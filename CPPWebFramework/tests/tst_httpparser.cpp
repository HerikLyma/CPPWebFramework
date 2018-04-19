#include "tst_httpparser.h"

void TST_HttpParser::test()
{
    QByteArray req(simpleRequest());
    CWF::HttpParser parser(req);

    QVERIFY2(parser.getCookies().size() == 1, "Should be 1");
    QVERIFY2(parser.getUrl() == "/", "Should be /");
    QVERIFY2(parser.getHttpVersion().endsWith("1.1"), "Should be 1.1");
    QVERIFY2(parser.getMethod() == "GET", "Should be GET");
    QVERIFY2(!parser.isMultiPart(), "Should be not be multiPart");
}

QByteArray TST_HttpParser::simpleRequest()
{
    QByteArray req;

    req  = "GET / HTTP/1.1\r\n";
    req += "Host: localhost:8080\r\n";
    req += "Connection: keep-alive\r\n";
    req += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n";
    req += "Cookie: uid=12345678901234567890\r\n\r\n";

    return req;
}

#include "tst_httpparser.h"

void TST_HttpParser::test()
{
    testGet();
    testPost();
    testPostWithFiles();
}

void TST_HttpParser::testGet()
{
    QByteArray req(buildGetRequest());
    CWF::HttpParser parser(req);

    QVERIFY2(parser.getCookies().size() == 1, "Should be 1");
    QVERIFY2(parser.getUrl() == "/home", "Should be /home");
    QVERIFY2(parser.getParameter("id").toInt() == 10, "Should be 10");
    QVERIFY2(parser.getParameter("nome") == "Herik", "Should be Herik");
    QVERIFY2(parser.getHttpVersion().endsWith("1.1"), "Should be 1.1");
    QVERIFY2(parser.getMethod() == "GET", "Should be GET");
    QVERIFY2(!parser.isMultiPart(), "Should be not be multiPart");

    req = buildGetRequestWithoutEndMsg();
    QVERIFY2(!CWF::HttpParser(req).isValid(), "Should be false");
    req = buildInvalidRequest();
    QVERIFY2(!CWF::HttpParser(req).isValid(), "Should be false");
}

void TST_HttpParser::testPost()
{
    QByteArray req(buildPostRequest('A'));
    CWF::HttpParser parser(req);

    QVERIFY2(parser.getCookies().size() == 1, "Should be 1");
    QVERIFY2(parser.getUrl() == "/home", "Should be /home");
    QVERIFY2(parser.getParameter("id").toInt() == 10, "Should be 10");
    QVERIFY2(parser.getParameter("nome") == "Herik", "Should be Herik");
    QVERIFY2(parser.getHttpVersion().endsWith("1.1"), "Should be 1.1");
    QVERIFY2(parser.getMethod() == "POST", "Should be POST");
    QVERIFY2(!parser.isMultiPart(), "Should be not be multiPart");

    req = buildPostRequest('B');
    QVERIFY2(CWF::HttpParser(req).getParameter("nome").isEmpty(), "Should be true");
    req = buildPostRequest('C');
    QVERIFY2(CWF::HttpParser(req).getParameter("id").toInt() == 10, "Should be 10");
    req = buildPostRequest('D');
    QVERIFY2(CWF::HttpParser(req).getParameter("id").isEmpty(), "Should be true");
}

void TST_HttpParser::testPostWithFiles()
{
    QByteArray req(buildPostRequestWithFiles());
    CWF::HttpParser parser(req);

    QVERIFY2(parser.getCookies().size() == 2, "Should be 2");
    QVERIFY2(parser.getUrl() == "/savefiles", "Should be savefiles");
    QVERIFY2(parser.getParameter("id") == "", "Should be 10");
    QVERIFY2(parser.getUploadedFiles().size() == 2, "Should be 2");
    QVERIFY2(parser.getHttpVersion().endsWith("1.1"), "Should be 1.1");
    QVERIFY2(parser.getMethod() == "POST", "Should be POST");
    QVERIFY2(parser.isMultiPart(), "Should be be multiPart");
}

QByteArray TST_HttpParser::buildGetRequest()
{
    QByteArray req;

    req  = "GET /home?id=10&nome=Herik&x HTTP/1.1\r\n";
    req += "Host: localhost:8080\r\n";
    req += "Connection: keep-alive\r\n";
    req += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n";
    req += "Cookie: sessionId=12345678901234567890\r\n\r\n";

    return req;
}

QByteArray TST_HttpParser::buildPostRequest(char condition)
{
    QByteArray req;

    req  = "POST /home HTTP/1.1\r\n";
    req += "Host: localhost:8080\r\n";
    req += "Connection: keep-alive\r\n";
    req += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n";
    req += "Content-Type: application/x-www-form-urlencoded\r\n";
    req += "Cookie: sessionId=\"12345678901234567890\"\r\n\r\n";
    if(condition == 'A')
        req += "id=10&nome=Herik";
    else if(condition == 'B')
        req += "id=10&nome";
    else if(condition == 'C')
        req += "id=10";
    else if(condition == 'D')
        req += "id";
    return req;
}

QByteArray TST_HttpParser::buildPostRequestWithFiles()
{
    QByteArray req;

    req  = "POST /savefiles?id= HTTP/1.1\r\n";
    req += "Host: localhost:8080\r\n";
    req += "Connection: keep-alive\r\n";
    req += "Content-Length: 890\r\nCache-Control: max-age=0\r\n";
    req += "Origin: http://localhost:8080\r\n";
    req += "Upgrade-Insecure-Requests: 1\r\n";
    req += "Cookie: xxx=10; yyy=20\r\n";
    req += "Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryRfRRkSFRgWLngq8y\r\n";
    req += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n";
    req += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n";
    req += "Referer: http://localhost:8080/pages/savefiles.html\r\n";
    req += "Accept-Encoding: gzip, deflate, br\r\n";
    req += "Accept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n";
    req += "------WebKitFormBoundaryRfRRkSFRgWLngq8y\r\nContent-Disposition: form-data; name=\"theFile\"; filename=\"test.txt\"\r\nContent-Type: text/plain\r\n\r\naaaaaaaa\n\r\n------WebKitFormBoundaryRfRRkSFRgWLngq8y\r\nContent-Disposition: form-data; name=\"theFile2\"; filename=\"test2.txt\"\r\nContent-Type: text/plain\r\n\r\naaaaaaaa\n\r\n------WebKitFormBoundaryRfRRkSFRgWLngq8y\r\nContent-Disposition: form-data; name=\"theFile3\"; filename=\"\"\r\nContent-Type: application/octet-stream\r\n\r\n\r\n------WebKitFormBoundaryRfRRkSFRgWLngq8y\r\nContent-Disposition: form-data; name=\"theFile4\"; filename=\"\"\r\nContent-Type: application/octet-stream\r\n\r\n\r\n------WebKitFormBoundaryRfRRkSFRgWLngq8y\r\nContent-Disposition: form-data; name=\"theFile5\"; filename=\"\"\r\nContent-Type: application/octet-stream\r\n\r\n\r\n------WebKitFormBoundaryRfRRkSFRgWLngq8y\r\nContent-Disposition: form-data; name=\"moo\"\r\n\r\nSend Files\r\n------WebKitFormBoundaryRfRRkSFRgWLngq8y--\r\n";

    return req;
}

QByteArray TST_HttpParser::buildGetRequestWithoutEndMsg()
{
    QByteArray req;

    req  = "GET /home?id=10&nome=Herik HTTP/1.1\r\n";
    req += "Host: localhost:8080\r\n";
    req += "Connection: keep-alive";

    return req;
}

QByteArray TST_HttpParser::buildInvalidRequest()
{
    return "GET HTTP/1.1\r\n\r\n";
}

#include "tst_request.h"


void TST_Request::test()
{
    QTcpSocket socket;
    CWF::QMapThreadSafety<QString, CWF::Session *> sessions;
    CWF::Configuration configuration;
    CWF::Request request(socket, sessions, configuration);
    ClientTest client;
    QMap<QByteArray, QByteArray> parameters({{"a", "Test"}, {"b", "Test"}, {"c", "true"},
                                             {"d", ""}  , {"e", ""}  ,{"h", "10"}, {"i", "10"},
                                             {"j", "10"}, {"k", "10"},{"l", "10"}, {"m", "10"},
                                             {"n", "10"}, {"o", "10"},{"p", "10"}, {"q", "10"}});
    request.fillQObject(&client, parameters);


    QVERIFY2(client.getA() == "Test", "Should be equal 'Test'");
    QVERIFY2(client.getB() == "Test", "Should be equal 'Test'");
    QVERIFY2(client.getC(), "Should return 'true'");
    QVERIFY2(client.getD() == ' ', "Should be equal ' '");
    QVERIFY2(client.getE() == ' ', "Should be equal ' '");
    QVERIFY2(client.getH() == 10, "Should be equal 10");
    QVERIFY2(client.getI() == 10, "Should be equal 10");
    QVERIFY2(client.getJ() == 10, "Should be equal 10");
    QVERIFY2(client.getK() == 10, "Should be equal 10");
    QVERIFY2(client.getL() == 10, "Should be equal 10");
    QVERIFY2(client.getM() == 10, "Should be equal 10");
    QVERIFY2(client.getN() == 10, "Should be equal 10");
    QVERIFY2(client.getO() == 10, "Should be equal 10");
    QVERIFY2(client.getP() <= 10, "Should be <= 10");
    QVERIFY2(client.getQ() <= 10, "Should be <= 10");
}

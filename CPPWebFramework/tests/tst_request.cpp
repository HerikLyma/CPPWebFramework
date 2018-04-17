#include "tst_request.h"


void TST_Request::test()
{
    QTcpSocket socket;
    CWF::QMapThreadSafety<QString, CWF::Session *> sessions;
    CWF::Configuration configuration;
    CWF::Request request(socket, sessions, configuration);
    ClientTest client;
    QMap<QByteArray, QByteArray> parameters({{"a", "Test"}});
    request.fillQObject(&client, parameters);

    QVERIFY2(client.getA() == "Test", "Should be equal 'Test'");
}

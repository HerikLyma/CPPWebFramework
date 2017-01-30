#include "tst_configuration.h"

void TST_Configuration::test()
{
    CWF::Configuration configuration("");
    configuration.setHost(QHostAddress("127.0.0.1"));
    configuration.setPort(8080);

    QVERIFY2(configuration.getHost().toString() == "127.0.0.1", "Should be 127.0.0.1");
    QVERIFY2(configuration.getPort() == 8080, "Should be 8080");
}

#include "tst_configuration.h"

void TST_Configuration::test()
{
    CWF::Configuration configuration("");
    configuration.setHost(QHostAddress("127.0.0.1"));
    configuration.setPort(8080);
    configuration.setDomain("www.test.com.xyz");
    configuration.setMaxThread(200);
    configuration.setCleanupInterval(1000);
    configuration.setMaxUploadFile(10000);
    configuration.setPath("/home/Test/server");
    configuration.setSessionExpirationTime(1000);
    configuration.setSslCertFile("my.cert");
    configuration.setSslKeyFile("my.key");
    configuration.setLogFilePath("/log");
    configuration.setTimeOut(60000);


    QVERIFY2(configuration.getHost().toString() == "127.0.0.1", "Should be 127.0.0.1");
    QVERIFY2(configuration.getPort() == 8080, "Should be 8080");
    QVERIFY2(configuration.getDomain() == "www.test.com.xyz", "Should be www.test.com.xyz");
    QVERIFY2(configuration.getMaxThread() == 200, "Should be 200");
    QVERIFY2(configuration.getCleanupInterval() == 1000, "Should return 1000");
    QVERIFY2(configuration.getMaxUploadFile() == 10000, "Should return 10000");
    QVERIFY2(configuration.getPath() == "/home/Test/server", "Should be /home/Test/server");
    QVERIFY2(configuration.getSessionExpirationTime() == 1000, "Should return 1000");
    QVERIFY2(configuration.getSslCertFile() == "my.cert", "Should be my.cert");
    QVERIFY2(configuration.getSslKeyFile() == "my.key", "Should be my.key");
    QVERIFY2(configuration.getLogFilePath() == "/log", "Should be /log");
    QVERIFY2(configuration.getTimeOut() == 60000, "Should return 60000");
}

void TST_Configuration::testReadFromFile()
{    
    QString path(QDir::currentPath() + "/server");
    QFile file(path + "/config/CPPWeb.ini");
    file.open(QIODevice::WriteOnly);

    file.write("[config]\n");
    file.write("host=127.0.0.1\n");
    file.write("port=8080\n");
    file.write("maxThread=200\n");
    file.write("cleanupInterval=60000\n");
    file.write("timeOut=60000\n");
    file.write("sessionExpirationTime=6000\n");
    file.write("maxUploadFile=20971520\n");
    file.write("path=" + path.toLatin1() + "\n");
    file.write("suffix=.xhtml\n");
    file.write("logFilePath=/config/log/\n");
    file.write("sslKeyFile=/config/ssl/my.key\n");
    file.write("sslCertFile=/config/ssl/my.cert\n");
    file.write("indexPage=/config/cppwebserverpages/index\n");
    file.write("accessCPPWebIni=false\n");
    file.write("accessServerPages=true");

    file.close();

    CWF::Configuration configuration(path);
    QVERIFY2(configuration.getHost().toString() == "127.0.0.1", "Should be 127.0.0.1");
    QVERIFY2(configuration.getPort() == 8080, "Should be 8080");
    QVERIFY2(configuration.getMaxThread() == 200, "Should be 200");
    QVERIFY2(configuration.getCleanupInterval() == 60000, "Should return 60000");
    QVERIFY2(configuration.getTimeOut() == 60000, "Should return 60000");
    QVERIFY2(configuration.getSessionExpirationTime() == 6000, "Should return 6000");
    QVERIFY2(configuration.getMaxUploadFile() == 20971520, "Should return 20971520");
    QVERIFY2(configuration.getPath() == path, QString("Should be " + path).toStdString().data());
    QVERIFY2(configuration.getLogFilePath().endsWith("log") == true, "Should be true");
    QVERIFY2(configuration.getSslCertFile().endsWith("my.cert") == true, "Should be true");
    QVERIFY2(configuration.getSslKeyFile().endsWith("my.key") == true, "Should be true");
}

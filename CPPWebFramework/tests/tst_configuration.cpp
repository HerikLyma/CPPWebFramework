#include "tst_configuration.h"

void TST_Configuration::test()
{
    QString path(QDir::currentPath() + "/server");
    QFile f(path + "/config/CPPWeb.ini");
    if(f.exists())
        QVERIFY2(f.remove(), "Should return true");

    QVERIFY2(CWF::Configuration("").isValid() == false, "Shoud return false.");


    if(!QDir(path).exists())
        QVERIFY2(QDir().mkdir(path), "Could not create server folder");
    if(!QDir(path + "/config").exists())
        QVERIFY2(QDir().mkdir(path + "/config"), "Could not create server config");
    QFile file(path + "/config/CPPWeb.ini");
    QVERIFY2(file.open(QIODevice::WriteOnly), "Could not create CPPWeb.ini file");

    file.write("[config]\n");
    file.write("host=127.0.0.1\n");
    file.write("port=8080\n");
    file.write("maxThread=200\n");
    file.write("cleanupInterval=60000\n");
    file.write("timeOut=60000\n");
    file.write("sessionExpirationTime=6000\n");
    file.write("maxUploadFile=20971520\n");
    file.write("logFilePath=/config/log/\n");
    file.write("sslKeyFile=/config/ssl/my.key\n");
    file.write("sslCertFile=/config/ssl/my.cert\n");
    file.write("indexPage=/config/cppwebserverpages/index\n");
    file.write("accessCPPWebIni=false\n");
    file.write("accessServerPages=true");

    file.close();


    CWF::Configuration configuration(path);
    QVERIFY2(configuration.getHost().toString() == "127.0.0.1", "Should be Any");
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
    QVERIFY2(CWF::Configuration("").isValid(), "Shoud return true.");
}

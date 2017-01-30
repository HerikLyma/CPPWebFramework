#include "tst_filemanager.h"

void TST_FileManager::test()
{
    CWF::FileManager fileManager;
    QString file("index.html");
    QVERIFY2(fileManager.fileExtention(file) == "html", "Should be html");

    fileManager.putFirstBar(file);
    QVERIFY2(file == "/index.html", "Should be /index.html");

    fileManager.removeFirstBar(file);
    QVERIFY2(file == "index.html", "Should be index.html");

    file += "/";
    fileManager.removeLastBar(file);
    QVERIFY2(file == "index.html", "Should be index.html");
    QVERIFY2(fileManager.extract(file, '.') == "html", "Should be html");

    QFile::FileError fileErro;
    QVERIFY2(fileManager.readAll(QDir::currentPath() + "/server/config/CPPWeb.ini", fileErro).size() > 0, "Should be > 0");
}

#include <QString>
#include <QtTest>
#include <cwf/configuration.h>

class ConfigurationTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testCase()
    {
        CWF::Configuration conf;
        QVERIFY2(conf.getTimeOut() == 30000, "Failure");
    }
};

QTEST_APPLESS_MAIN(ConfigurationTest)

#include "tst_configurationtest.moc"

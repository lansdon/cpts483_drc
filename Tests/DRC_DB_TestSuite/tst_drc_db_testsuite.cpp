#include <QString>
#include <QtTest>

class DRC_DB_TestSuite : public QObject
{
    Q_OBJECT

public:
    DRC_DB_TestSuite();

private Q_SLOTS:
    void testCase1();
};

DRC_DB_TestSuite::DRC_DB_TestSuite()
{
}

void DRC_DB_TestSuite::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(DRC_DB_TestSuite)

#include "tst_drc_db_testsuite.moc"

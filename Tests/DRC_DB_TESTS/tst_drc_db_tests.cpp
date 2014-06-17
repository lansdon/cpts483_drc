#include <QString>
#include <QtTest>

class DRC_DB_TESTS : public QObject
{
    Q_OBJECT

public:
    DRC_DB_TESTS();

private Q_SLOTS:
    void testCase1();
};

DRC_DB_TESTS::DRC_DB_TESTS()
{
}

void DRC_DB_TESTS::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(DRC_DB_TESTS)

#include "tst_drc_db_tests.moc"

#include <QString>
#include <QtTest>

class DBTestSuiteTest : public QObject
{
    Q_OBJECT

public:
    DBTestSuiteTest();

private Q_SLOTS:
    void DB_Creation();
};

DBTestSuiteTest::DBTestSuiteTest()
{
}

void DBTestSuiteTest::DB_Creation()
{

}

QTEST_APPLESS_MAIN(DBTestSuiteTest)

#include "tst_dbtestsuitetest.moc"

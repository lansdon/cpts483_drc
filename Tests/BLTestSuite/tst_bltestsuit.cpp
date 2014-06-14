#include <QString>
#include <QtTest>

#include "personvalidator.h"

class BLTestSuit : public QObject
{
    Q_OBJECT

public:
    BLTestSuit();

private Q_SLOTS:
    void testCase1();
    void testPersonValidator();
};

BLTestSuit::BLTestSuit()
{
}

void BLTestSuit::testCase1()
{
    QVERIFY2(true, "Failure");
}

void BLTestSuit::testPersonValidator()
{
    PersonValidator pVal;
    bool success = true;
    std::string errorMessage = "";
    Person person;
    success = pVal.Validate(&person, errorMessage);

    if (success == true) QVERIFY2(true, "Success!");
}

QTEST_APPLESS_MAIN(BLTestSuit)

#include "tst_bltestsuit.moc"

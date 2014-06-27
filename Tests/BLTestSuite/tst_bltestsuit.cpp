#include <QString>
#include <QtTest>

#include "Person.h"
#include "party.h"
#include "mediationprocess.h"
#include "stateupdate.h"

class BLTestSuit : public QObject
{
    Q_OBJECT

public:
    BLTestSuit();

private Q_SLOTS:
    void testInitiatedValidName();
};

BLTestSuit::BLTestSuit()
{
}

void BLTestSuit::testInitiatedValidName()
{
    Person person;
    person.setName("SomeName", "SomeMiddle", "SomeLast");

    Party party;
    party.SetPrimary(&person);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party);

    QString errorMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage);
    success &= (mediationProcess.getStateTransition() == PROCESS_STATE_INITIATED);
    QVERIFY2(success, "Successful");
}


QTEST_APPLESS_MAIN(BLTestSuit)

#include "tst_bltestsuit.moc"

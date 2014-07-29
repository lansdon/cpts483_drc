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
    // The approach for these tests is to test the checks we wanted to catch,
    // not necessarily related to any particular state or function.
    // Each function however builds on the previous.
    // For example, if providing a name was tested in the first function,
    // it is assumed that for all the remaining tests a name is provided.

    void testOnlyNameProvided(); // tests the progress out of NONE
    void testNoNameProvided();

/*    void testInfoOnlyChecked();
    void testInfoOnlyNotChecked();

    void testTwoDuplicateClients();
    void testTwoDifferentClients();

    void testOneClientOnly();
    void testTwoUniqueClients();

    void testCoachingSession();

    void testAttorneyInfoProvided();
    void testAttorneyInfoMissing();

    void testSufficientContactInfo();
    void testInsufficientContactInfo();

    void testFeesRecorded();
    void testNoFeesRecorded();

    void testMediatiorsRecorded();
    void testNoMediatorsRecorded();

    void testSessionConfirmed();
    void testSessionNotConfirmed();

    void testFeesPaid();
    void testFeesNotPaid(); */
};

BLTestSuit::BLTestSuit()
{
}

/* Test no name provided.
 *
 * Expected result:
 *      success = false
 *      internalState = PROCESS_INTERNAL_STATE_NONE
 *      externalState = PROCESS_STATE_NONE
 */
void BLTestSuit::testNoNameProvided()
{
    Person person;

    Party party;
    party.SetPrimary(&person);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party);

    QString errorMessage = "";
    StateUpdate stateUpdate;
    QString stateMessage="";
    bool success = !stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);   // Flipping success since we expect failure
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_NONE);
         success &= (mediationProcess.GetState() == PROCESS_STATE_NONE);
    QVERIFY2(success, "Successful: No name provided fails");
}

/* Test name provided.
 *
 * Expected result:
 *      success = true
 *      internalState = PROCESS_INTERNAL_STATE_INITIATED
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testOnlyNameProvided()
{
    Person person;
    person.setName("SomeFirst", "SomeMiddle", "SomeLast");

    Party party;
    party.SetPrimary(&person);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party);

    QString errorMessage = "";
    QString stateMessage="";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_INITIATED);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "Successful: Name provided succeeds");
}

/* Test info only.
 *
 * Expected result:
 *      success = true
 *      internalState = PROCESS_INTERNAL_STATE_INITIATED
 *      externalState = PROCESS_STATE_PENDING
 */
//void BLTestSuit::testNameProvided()
//{
//    Person person;
//    person.setName("SomeFirst", "SomeMiddle", "SomeLast");

//    Party party;
//    party.SetPrimary(&person);

//    MediationProcess mediationProcess;
//    mediationProcess.AddParty(&party);

//    QString errorMessage = "";
//    StateUpdate stateUpdate;
//    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage);
//         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_INITIATED);
//         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
//    QVERIFY2(success, "Successful: Name provided succeeds");
//}

///* Test Initiated State with valid data:
// *      MediationProcess contains at least one party with a primary that has a valid name
// * Expected result: MediationProcess should be in PROCESS_STATE_INITIATED
// */
//void BLTestSuit::testInitiatedValid()
//{
//    Person person;
//    person.setName("SomeName", "SomeMiddle", "SomeLast");

//    Party party;
//    party.SetPrimary(&person);

//    MediationProcess mediationProcess;
//    mediationProcess.AddParty(&party);

//    QString errorMessage = "";
//    StateUpdate stateUpdate;
//    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage);
//    success &= (mediationProcess.getStateTransition() == PROCESS_STATE_INITIATED);
//    QVERIFY2(success, "Successful: MediationProcess in state PROCESS_STATE_INITIATED");
//}

///* Test Initiated State with invalid data:
// *      MediationProcess does not contain any party that has a primary with a valid name
// * Expected result: MediationProcess should be in PROCESS_STATE_INITIATED
// */
//void BLTestSuit::testInitiatedInvalid()
//{
//    Person person;
//    person.setName("", "", "");

//    Party party;
//    party.SetPrimary(&person);

//    MediationProcess mediationProcess;
//    mediationProcess.AddParty(&party);

//    QString errorMessage = "";
//    StateUpdate stateUpdate;
//    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage);
//    success &= (mediationProcess.getStateTransition() == PROCESS_STATE_NONE);
//    QVERIFY2(success, "Successful: MediationProcess in state PROCESS_STATE_NONE");
//}

///* Test ReadyToSchedule State with valid data:
// *      The primary person in each party should have a phone number + name or email
// * Expected result: MediationProcess should be in PROCESS_STATE_READY_TO_SCHEDULE
// */
//void BLTestSuit::testReadyToScheduleValid()
//{
//    Person person;
//    person.setName("SomeName", "SomeMiddle", "SomeLast");
//    person.setPrimaryPhone("5555555555");
//    person.setCity("Kennewick");
//    person.setStreet("123 Fake Street");
//    person.setCounty("Benton");
//    person.setZip("99337");
//    person.setEmail("someguy@email.com");

//    Person person2;
//    person2.setName("SomeName2", "SomeMiddle2", "SomeLast2");
//    person.setPrimaryPhone("1111111111");
//    person.setCity("Pasco");
//    person.setStreet("789 NoPlace Rd");
//    person.setCounty("Franklin");
//    person.setZip("99301");
//    person.setEmail("someguy2@email.com");

//    Party party;
//    party.SetPrimary(&person);

//    Party party2;
//    party2.SetPrimary(&person2);

//    MediationProcess mediationProcess;
//    mediationProcess.AddParty(&party);
//    mediationProcess.AddParty(&party2);

//    QString errorMessage = "";
//    StateUpdate stateUpdate;
//    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage);
//    success &= (mediationProcess.getStateTransition() == PROCESS_STATE_READY_TO_SCHEDULE);
//    QVERIFY2(success, "Successful: MediationProcess in state PROCESS_STATE_READY_TO_SCHEDULE");
//}

///* Test ReadyToSchedule State with invalid data:
// *      The primary person in each party does not have a phone number + name or email
// * Expected result: MediationProcess should be in PROCESS_STATE_INITIATED
// */
//void BLTestSuit::testReadyToScheduleInvalid()
//{
//    Person person;
//    person.setName("SomeName", "SomeMiddle", "SomeLast");

//    Person person2;
//    person2.setName("SomeName2", "SomeMiddle2", "SomeLast2");

//    Party party;
//    party.SetPrimary(&person);

//    Party party2;
//    party2.SetPrimary(&person2);

//    MediationProcess mediationProcess;
//    mediationProcess.AddParty(&party);
//    mediationProcess.AddParty(&party2);

//    QString errorMessage = "";
//    StateUpdate stateUpdate;
//    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage);
//    success &= (mediationProcess.getStateTransition() == PROCESS_STATE_INITIATED);
//    QVERIFY2(success, "Successful: MediationProcess in state PROCESS_STATE_INITIATED");
//}

///* Test Scheduled State with valid data:
// *      The mediation sessions vector in the mediation process object should not be empty
// * Expected result: MediationProcess should be in PROCESS_STATE_SCHEDULED
// */
//void BLTestSuit::testScheduledValid()
//{
//    Person person;
//    person.setName("SomeName", "SomeMiddle", "SomeLast");
//    person.setPrimaryPhone("5555555555");
//    person.setCity("Kennewick");
//    person.setStreet("123 Fake Street");
//    person.setCounty("Benton");
//    person.setZip("99337");
//    person.setEmail("someguy@email.com");

//    Person person2;
//    person2.setName("SomeName2", "SomeMiddle2", "SomeLast2");
//    person.setPrimaryPhone("1111111111");
//    person.setCity("Pasco");
//    person.setStreet("789 NoPlace Rd");
//    person.setCounty("Franklin");
//    person.setZip("99301");
//    person.setEmail("someguy2@email.com");

//    Party party;
//    party.SetPrimary(&person);

//    Party party2;
//    party2.SetPrimary(&person2);

//    MediationProcess mediationProcess;
//    mediationProcess.AddParty(&party);
//    mediationProcess.AddParty(&party2);

//    mediationProcess.setMediationSessionVector(new MediationSessionVector());

//    QString errorMessage = "";
//    StateUpdate stateUpdate;
//    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage);
//    success &= (mediationProcess.getStateTransition() == PROCESS_STATE_SCHEDULED);
//    QVERIFY2(success, "Successful: MediationProcess in state PROCESS_STATE_SCHEDULED");
//}

///* Test Scheduled State with invvalid data:
// *      The mediation sessions vector in the mediation process object should is empty
// * Expected result: MediationProcess should be in PROCESS_STATE_READY_TO_SCHEDULE
// */
//void BLTestSuit::testScheduledInvalid()
//{
//    Person person;
//    person.setName("SomeName", "SomeMiddle", "SomeLast");
//    person.setPrimaryPhone("5555555555");
//    person.setCity("Kennewick");
//    person.setStreet("123 Fake Street");
//    person.setCounty("Benton");
//    person.setZip("99337");
//    person.setEmail("someguy@email.com");

//    Person person2;
//    person2.setName("SomeName2", "SomeMiddle2", "SomeLast2");
//    person.setPrimaryPhone("1111111111");
//    person.setCity("Pasco");
//    person.setStreet("789 NoPlace Rd");
//    person.setCounty("Franklin");
//    person.setZip("99301");
//    person.setEmail("someguy2@email.com");

//    Party party;
//    party.SetPrimary(&person);

//    Party party2;
//    party2.SetPrimary(&person2);

//    MediationProcess mediationProcess;
//    mediationProcess.AddParty(&party);
//    mediationProcess.AddParty(&party2);

//    QString errorMessage = "";
//    StateUpdate stateUpdate;
//    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage);
//    success &= (mediationProcess.getStateTransition() == PROCESS_STATE_READY_TO_SCHEDULE);
//    QVERIFY2(success, "Successful: MediationProcess in state PROCESS_STATE_READY_TO_SCHEDULE");
//}

QTEST_APPLESS_MAIN(BLTestSuit)

#include "tst_bltestsuit.moc"

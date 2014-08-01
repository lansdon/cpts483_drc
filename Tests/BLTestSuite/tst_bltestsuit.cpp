#include <QString>
#include <QtTest>

#include "Person.h"
#include "party.h"
#include "mediationprocess.h"
#include "stateupdate.h"
#include "mediationsession.h"

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
    void testNameProvided();

    void testInfoOnlyChecked();
    void testInfoOnlyNotChecked();

    void testTwoDuplicateClients();
    void testTwoDifferentClients();

    void testOneClientOnly();

    void testCoachingSession();

    void testAttorneyInfoProvided();
    void testAttorneyInfoMissing();

    void testSufficientContactInfoAddress();
    void testInsufficientContactInfo();

    void testFeesRecorded();
    void testNoFeesRecorded();

    void testMediatorsRecorded();
    void testNoMediatorsRecorded();

    void testSessionConfirmed();
    void testSessionNotConfirmed();

    void testAgreementReachedSufficientContactInfo();
    void testAgreementReachedInsufficientContactInfo();

    void testOtherOutcomeSufficientContactInfo();
    void testOtherOutcomeInsufficientContactInfo();
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
 *      internalState = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
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
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Name provided");
}

/* Test info only.
 *
 * Expected result:
 *      success = true
 *      internalState = PROCESS_INTERNAL_STATE_INFO_ONLY
 *      externalState = PROCESS_STATE_CLOSED_NO_SESSION
 */
void BLTestSuit::testInfoOnlyChecked()
{
    Person person;
    person.setName("SomeFirst", "SomeMiddle", "SomeLast");

    Party party;
    party.SetPrimary(&person);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party);

    mediationProcess.SetInfoOnly(true);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_INFO_ONLY);
         success &= (mediationProcess.GetState() == PROCESS_STATE_CLOSED_NO_SESSION);
    QVERIFY2(success, "FAILURE!! Info only");
}

/* Test info only not checked.
 * Expected result:
 *      success = true
 *      internalState = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testInfoOnlyNotChecked()
{
    Person person;
    person.setName("SomeFirst", "SomeMiddle", "SomeLast");

    Party party;
    party.SetPrimary(&person);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party);

    mediationProcess.SetInfoOnly(false);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Info only not checked");
}

/* Test name provided.
 * Expected result:
 *      success = true
 *      internalState = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testNameProvided()
{
    Person person;
    person.setName("SomeFirst", "SomeMiddle", "SomeLast");

    Party party;
    party.SetPrimary(&person);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Name provided");
}

/* Test Two Duplicate Clients
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_INITIATED
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testTwoDuplicateClients()
{
    Person person1;
    person1.setName("SomeFirst", "SomeMiddle", "SomeLast");
    Party party1;
    party1.SetPrimary(&person1);

    Person person2;
    person2.setName("SomeFirst", "SomeMiddle", "SomeLast");
    Party party2;
    party2.SetPrimary(&person2);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_INITIATED);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Test two duplicate clients");
}

/* Test Two Different Clients
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testTwoDifferentClients()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    Party party1;
    party1.SetPrimary(&person1);

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    Party party2;
    party2.SetPrimary(&person2);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Test two unique clients");
}

/* Test One Client Only
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testOneClientOnly()
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
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! One client only");
}

/* Test Sufficient Contact Info with street address
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_CLIENT_INFO
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testSufficientContactInfoAddress()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("somefirst@email.com");
    person1.setStreet("123 Fake Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    person1.setAttorney("asdf");
    Party party1;
    party1.SetPrimary(&person1);

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("somefirst2@amil.com");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    person2.setAttorney("qwerty");
    Party party2;
    party2.SetPrimary(&person2);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_CLIENT_INFO);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Test sufficient contact info with stree addresses");
}

/* Test Insufficient Contact Info
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testInsufficientContactInfo()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
//    person1.setAttorney("asdf");
    Party party1;
    party1.SetPrimary(&person1);

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    Party party2;
    party2.SetPrimary(&person2);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Test sufficient contact info with stree addresses");
}

/* Test state gets advanced with one client when process type is coaching session
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testCoachingSession()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    Party party1;
    party1.SetPrimary(&person1);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);

    mediationProcess.SetSessionType(COACHING_SESSION);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Test coaching session");
}

/* Test that both clients have attorney name set
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_CLIENT_INFO
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testAttorneyInfoProvided()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("Bob Loblaw");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setAttorney("Douchey McDoucherson");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    Party party2;
    party2.SetPrimary(&person2);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_CLIENT_INFO);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Attorney Info Provided");
}

/* Test that both clients have attorney name set
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testAttorneyInfoMissing()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("Bob Loblaw");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    Party party1;
    party1.SetPrimary(&person1);

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    Party party2;
    party2.SetPrimary(&person2);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Attorney Info Missing");
}

/* Test when session is set to confirmed
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_SCHEDULED
 *      externalState = PROCESS_STATE_SCHEDULED
 */
void BLTestSuit::testSessionConfirmed()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("adfswerwesdfwerty");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("120");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setAttorney("dfwerty");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("200");

    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_CONFIRMED);
    mediationSession.setClientSessionDataVector(clientSessionData);

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);


    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_SCHEDULED);
         success &= (mediationProcess.GetState() == PROCESS_STATE_SCHEDULED);
    QVERIFY2(success, "FAILURE!! Test session set to confirmed");
}

/* Test when session is set to confirmed
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_FEES_RECORDED
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testSessionNotConfirmed()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("asdf");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("120");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setAttorney("dfwerty");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("200");

    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_NONE);
    mediationSession.setClientSessionDataVector(clientSessionData);

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);


    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_FEES_RECORDED);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Test session not confirmed");
}

/* Test that fees have been recorded for the session
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_SCHEDULED
 *      externalState = PROCESS_STATE_SCHEDULED
 */
void BLTestSuit::testFeesRecorded()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("asdfwerty");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("200");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setAttorney("dfwerty");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("150");

    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_CONFIRMED);
    mediationSession.setClientSessionDataVector(clientSessionData);

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);


    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_SCHEDULED);
         success &= (mediationProcess.GetState() == PROCESS_STATE_SCHEDULED);
    QVERIFY2(success, "FAILURE!! Test fees recorded.");
}

/* Test that no fees have been recorded for the session
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_SCHEDULED
 *      externalState = PROCESS_STATE_SCHEDULED
 */
void BLTestSuit::testNoFeesRecorded()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("asdfwerty");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("200");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setAttorney("dfwerty");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("150");


    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_CONFIRMED);
    mediationSession.setClientSessionDataVector(clientSessionData);

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);


    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_SCHEDULED);
         success &= (mediationProcess.GetState() == PROCESS_STATE_SCHEDULED);
    QVERIFY2(success, "FAILURE!! Test fees not recorded");
}

/* Test to see if mediators have been added
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_MEDIATORS_ASSIGNED
 *      externalState = PROCESS_STATE_SCHEDULED
 */
void BLTestSuit::testMediatorsRecorded()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("asdfwerty");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("200");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setAttorney("dfwerty");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("150");

    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_CONFIRMED);
    mediationSession.setClientSessionDataVector(clientSessionData);
    mediationSession.setMediator1("Jim bob");
    mediationSession.setMediator2("Jill");

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_MEDIATORS_ASSIGNED);
         success &= (mediationProcess.GetState() == PROCESS_STATE_SCHEDULED);
    QVERIFY2(success, "FAILURE!! Test mediators set");
}

/* Test to see if no mediators have been added
 * Expected result: success = true
 *      internalState = PROCESS_INTERNAL_STATE_SCHEDULED
 *      externalState = PROCESS_STATE_SCHEDULED
 */
void BLTestSuit::testNoMediatorsRecorded()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("asdfwerty");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("200");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setAttorney("dfwerty");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("150");

    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_CONFIRMED);
    mediationSession.setClientSessionDataVector(clientSessionData);

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetInternalState() == PROCESS_INTERNAL_STATE_SCHEDULED);
         success &= (mediationProcess.GetState() == PROCESS_STATE_SCHEDULED);
    QVERIFY2(success, "FAILURE!! Test mediators not set.");
}

/* Test Agreement reached with sufficient contact info
 *      externalState = PROCESS_STATE_CLOSED_SCHEDULED
 */
void BLTestSuit::testAgreementReachedSufficientContactInfo()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("asdfwerty");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("200");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setAttorney("dfwerty");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("150");

    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_CONFIRMED);
    mediationSession.setClientSessionDataVector(clientSessionData);
    mediationSession.setOutcome(SESSION_OUTCOME_AGREEMENT);

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetState() == PROCESS_STATE_SCHEDULED);
    QVERIFY2(success, "FAILURE!! Test agreement reached with sufficient contact info");
}

/* Test agreement reached with with insufficient contact info
 *      externalState = PROCESS_STATE_PENDING
 */
void BLTestSuit::testAgreementReachedInsufficientContactInfo()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("asdfwerty");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("200");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("150");

    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_CONFIRMED);
    mediationSession.setClientSessionDataVector(clientSessionData);
    mediationSession.setOutcome(SESSION_OUTCOME_AGREEMENT);

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetState() == PROCESS_STATE_PENDING);
    QVERIFY2(success, "FAILURE!! Test agreement reached with insufficient contact info");
}

/* Test other outcome with sufficient contact info
 *      externalState = PROCESS_STATE_CLOSED_NO_SESSION
 */
void BLTestSuit::testOtherOutcomeSufficientContactInfo()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("asdfwerty");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("200");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    person2.setPrimaryPhone("2222222222");
    person2.setEmail("someguy2@blah.com");
    person2.setAttorney("dfwerty");
    person2.setStreet("125 Fake Street");
    person2.setCity("Kennewick");
    person2.setState("Washington");
    person2.setZip("99337");
    person2.setCounty(COUNTY_BENTON);
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("150");

    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_CONFIRMED);
    mediationSession.setClientSessionDataVector(clientSessionData);
    mediationSession.setOutcome(SESSION_OUTCOME_FIRST_PARTY_WITHDREW);

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);


    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetState() == PROCESS_STATE_CLOSED_NO_SESSION);
    QVERIFY2(success, "FAILURE!! Test other outcome with sufficient contact info.");
}

/* Test other outcome with insufficient contact info
 *      externalState = PROCESS_STATE_CLOSED_NO_SESSION
 */
void BLTestSuit::testOtherOutcomeInsufficientContactInfo()
{
    Person person1;
    person1.setName("SomeFirst1", "SomeMiddle1", "SomeLast1");
    person1.setPrimaryPhone("5555555555");
    person1.setEmail("someguy@blah.com");
    person1.setAttorney("asdfwerty");
    person1.setStreet("12 Street");
    person1.setCity("Kennewick");
    person1.setState("Washington");
    person1.setZip("99337");
    person1.setCounty(COUNTY_BENTON);
    Party party1;
    party1.SetPrimary(&person1);
    ClientSessionData client1Data;
    client1Data.setFee("200");

    Person person2;
    person2.setName("SomeFirst2", "SomeMiddle2", "SomeLast2");
    Party party2;
    party2.SetPrimary(&person2);
    ClientSessionData client2Data;
    client2Data.setFee("150");

    ClientSessionDataVector clientSessionData;
    clientSessionData.push_back(&client1Data);
    clientSessionData.push_back(&client2Data);

    MediationSession mediationSession;
    mediationSession.SetState(SESSION_STATE_CONFIRMED);
    mediationSession.setClientSessionDataVector(clientSessionData);
    mediationSession.setOutcome(SESSION_OUTCOME_FIRST_PARTY_WITHDREW);

    MediationSessionVector mediationSessions;
    mediationSessions.push_back(&mediationSession);

    MediationProcess mediationProcess;
    mediationProcess.AddParty(&party1);
    mediationProcess.AddParty(&party2);
    mediationProcess.setMediationSessionVector(&mediationSessions);

    QString errorMessage = "";
    QString stateMessage = "";
    StateUpdate stateUpdate;
    bool success = stateUpdate.StateCheck(&mediationProcess, errorMessage, stateMessage);
         success &= (mediationProcess.GetState() == PROCESS_STATE_CLOSED_NO_SESSION);
    QVERIFY2(success, "FAILURE!! Test other outcome with sufficient contact info");
}

// Old tests

/* Test Initiated State with valid data:
 *      MediationProcess contains at least one party with a primary that has a valid name
 * Expected result: MediationProcess should be in PROCESS_STATE_INITIATED
 */
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

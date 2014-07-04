#include "mpfilemaker.h"

MPFileMaker::MPFileMaker()
{
    mpVector = new MediationProcessVector();
    FileName = "test.mp";
    empty = "NULL";
}

void MPFileMaker::addMP(MediationProcess *mp)
{
    mpVector->push_back(mp);
}

void MPFileMaker::sendToFile()
{
    QFile file(FileName);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream fileStream(&file);
        parseToFile(fileStream);
        file.close();
    }
    else
        qDebug() << "error opening file.";

}

MediationProcessVector *MPFileMaker::getMedationProcessVector() const
{
    return mpVector;
}

void MPFileMaker::sendToFile(MediationProcessVector *MPVector)
{

    mpVector = MPVector;
    sendToFile();
}

void MPFileMaker::sendToFile(MediationProcess *MP)
{
    mpVector->clear();
    mpVector->push_back(MP);
    sendToFile();
}

void MPFileMaker::getFromFile()
{
    //file to parse
    QFile file(FileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream fileStream(&file);
        //QDataStream fileStream(&file);
        fileToParse(fileStream);
        file.close();
    }
    else
        qDebug() << "error opening file.";
}

void MPFileMaker::getFromFile(QString fileName)
{
    FileName = fileName;
    getFromFile();
}

void MPFileMaker::fileToParse(QTextStream &in)
{
    QString line;
     line = in.readLine();
     removeMPKeyword(line);
    int numberOfMPs = line.toInt();
    //MediationProcess *temp;

    mpVector->clear();
    for(int i = 0; i < numberOfMPs; i++)
    {

        mpVector->push_back(fileToProcessParse(in));
    }
}

void MPFileMaker::parseToFile(QTextStream &out)
{
    out << "NUMBER_OF_MEDIATIONS: ";
    out << (int)mpVector->size() << "\n";
    for(int i = 0; i < (int)mpVector->size();i++)
    {
        parseProcessToFile(out,mpVector->at(i));
    }
}
MediationProcess *MPFileMaker::fileToProcessParse(QTextStream &in)
{
    MediationProcess *temp = nullptr;
//    QString line;
//    unsigned int id;
//    QString creation, updated, mediationCreationDate;
//    uint state, activeState;
//    CountyIds countyid;
//    DisputeTypes disType;
//    ReferralTypes reftype;
//    bool spanish;
//    DisputeProcessInternalStates currState;
//    PartyVector parties;
//    MediationNotesVector notes;
//    MediationSessionVector sessions;
//    line = in.readLine();
//    removeMPKeyword(line);
//    id = line.toUInt();
//    creation = in.readLine();
//    removeMPKeyword(creation);
//    updated = in.readLine();
//    removeMPKeyword(updated);
//    line = in.readLine();
//    removeMPKeyword(line);
//    state = line.toUInt();
//    line = in.readLine();
//    removeMPKeyword(line);
//    activeState = line.toUInt();
//    mediationCreationDate = in.readLine();
//    removeMPKeyword(mediationCreationDate);
//    line = in.readLine();
//    removeMPKeyword(line);
//    countyid = (CountyIds)line.toInt();
//    line = in.readLine();
//    removeMPKeyword(line);
//    disType = (DisputeTypes)line.toInt();
//    line = in.readLine();
//    removeMPKeyword(line);
//    reftype = (ReferralTypes)line.toInt();
//    line = in.readLine();
//    removeMPKeyword(line);
//    spanish = line.toInt();
//    line = in.readLine();
//    removeMPKeyword(line);
//    currState = (DisputeProcessInternalStates)line.toInt();

//    parties = partiesVectorParse(in);
//    notes = processNotesParse(in);
//    sessions = sessionsVectorParse(in);
//    temp = new MediationProcess(parties, state, activeState, disType, QDateTime::fromString(mediationCreationDate), currState, countyid, notes, reftype, (bool)spanish, sessions);
//    temp = new MediationProcess(parties, )
//    temp->SetId(id);
//    temp->SetCreatedDate(QDateTime::fromString(creation));
//    temp->SetUpdatedDate(QDateTime::fromString(updated));


    return temp;
}
void MPFileMaker::removeMPKeyword(QString &value)
{
    int count = 0;
    while(value[count] != ' ')
    {
        count++;
    }
    count++;
    value.remove(0,count);
    //return value;
}

void MPFileMaker::parseProcessToFile(QTextStream &out, MediationProcess *mp)
{
    out << "MP_ID: ";
    out << mp->GetId() << "\n";
    out << "MP_DATABASE_OBJ_CREATION_DATE: ";
    out << mp->GetCreatedDate().toString() << "\n";
    out << "MP_DATABASE_OBJ_UPDATE_DATE: ";
    out << mp->GetUpdatedDate().toString() << "\n";
    out << "MP_STATE_TRANSITION: ";
    out << mp->getStateTransition() << "\n";
    out << "MP_ACTIVE_STATE_TRANSITION: ";
    out << mp->getActiveStateTransition() << "\n";
    out << "MP_CREATION_DATE: ";
    out << mp->GetCreatedDate().toString() << "\n";
    out << "MP_COUNTY_ID: ";
    out << mp->GetCountyId() << "\n";
    out << "MP_DISPUTE_TYPE: ";
    out << mp->GetDisputeType() << "\n";
    out << "MP_REFERAL_TYPE: ";
    out << mp->GetReferralType() << "\n";
    out << "MP_REQUIRES_SPANISH: ";
    out << mp->GetRequiresSpanish() << "\n";
    out << "MP_CURRENT_STATE: ";
    out << mp->GetState() << "\n";
    parsePartiesVector(out,mp->GetParties());
    parseProcessNotes(out, mp->GetNotes());
    parseSessionsVector(out, mp->getMediationSessionVector());

}

void MPFileMaker::parseSessionsVector(QTextStream &out, MediationSessionVector *msv)
{
    out << "NUMBER_OF_SESSIONS: ";
    out << (int)msv->size() << "\n";
    for(int i = 0; i < (int)msv->size(); i++)
    {
        parseSession(out,msv->at(i));
    }
}

MediationSessionVector MPFileMaker::sessionsVectorParse(QTextStream &in)
{
    QString line;
    MediationSessionVector *temp = new MediationSessionVector();//, extra;
    line = in.readLine();
    int numberOfSessions;
    removeMPKeyword(line);
    numberOfSessions = line.toInt();


    for(int i = 0; i < numberOfSessions; i++)
    {
        temp->push_back(sessionParse(in));
    }

    return *temp;
}

MediationSession *MPFileMaker::sessionParse(QTextStream &in)
{
    //QString line;
    MediationSession *temp = new MediationSession();
   //MediationSession *extra = new MediationSession();
    QString create, time;
    SessionStates state;
    QString fee1, fee2, fee3, fee4, income1, income2, income3;
    QString incomeOther;//, extraSting;
    QString stateqs, paid1qs, paid2qs, paid3qs, paid4qs;
    bool paid1, paid2, paid3, paid4;
    QString med1, med2, obs1, obs2;//, extraPointer;

    stateqs = in.readLine();
    create = in.readLine();
    time = in.readLine();
    fee1 = in.readLine();
    fee2 = in.readLine();
    fee3 = in.readLine();
    fee4 = in.readLine();
    paid1qs = in.readLine();
    paid2qs = in.readLine();
    paid3qs = in.readLine();
    paid4qs = in.readLine();
    income1 = in.readLine();
    income2 = in.readLine();
    income3 = in.readLine();
    incomeOther = in.readLine();
    med1 = in.readLine();
    med2 = in.readLine();
    obs1 = in.readLine();
    obs2 = in.readLine();

    removeMPKeyword(create);
    removeMPKeyword(time);
    removeMPKeyword(stateqs);
    state = (SessionStates)stateqs.toInt();
    removeMPKeyword(paid1qs);
    paid1 = paid1qs.toInt();
    removeMPKeyword(paid2qs);
    paid2 = paid2qs.toInt();
    removeMPKeyword(paid3qs);
    paid3 = paid3qs.toInt();
    removeMPKeyword(paid4qs);
    paid4 = paid4qs.toInt();
    removeMPKeyword(fee1);
    removeMPKeyword(fee2);
    removeMPKeyword(fee3);
    removeMPKeyword(fee4);
    removeMPKeyword(income1);
    removeMPKeyword(income2);
    removeMPKeyword(income3);
    removeMPKeyword(incomeOther);
    removeMPKeyword(med1);
    removeMPKeyword(med2);
    removeMPKeyword(obs1);
    removeMPKeyword(obs2);



    temp->SetState(state);
    temp->setMediationTime(QDateTime::fromString(time));
    temp->SetCreatedDate(QDateTime::fromString(create));
    temp->setFee1(fee1);
    temp->setFee1Paid(paid1);
    temp->setFee2(fee2);
    temp->setFee2Paid(paid2);
    temp->setFeeFamily(fee3);
    temp->setFeeFamilyPaid(paid3);
    temp->setFeeOther(fee4);
    temp->setFeeOtherPaid(paid4);
    temp->setIncomeFee1(income1);
    temp->setIncomeFee2(income2);
    temp->setIncomeFeeFamily(income3);
    temp->setIncomeFeeOther(incomeOther);
    temp->setMediator1(med1);
    temp->setMediator2(med2);
    temp->setObserver1(obs1);
    temp->setObserver2(obs2);


    return temp;
}

void MPFileMaker::parseSession(QTextStream &out, MediationSession *ms)
{
    out << "SESSION_STATE: ";
    out << ms->GetState() << "\n";
    out << "SESSION_CREATION_DATE: ";
    out << ms->GetCreatedDate().toString() << "\n";
    out << "SESSION_SCHEDULED_DATE: ";
    out << ms->getMediationTime().toString() << "\n";
    out << "SESSION_FEE1: ";
    out << ms->getFee1() << "\n";
    out << "SESSION_FEE2: ";
    out << ms->getFee2() << "\n";
    out << "SESSION_FEE_FAMILY: ";
    out << ms->getFeeFamily() << "\n";
    out << "SESSION_FEE_OTHER: ";
    out << ms->getFeeOther() << "\n";
    out << "SESSION_FEE1_PAID: ";
    out << ms->getFee1Paid() << "\n";
    out << "SESSION_FEE2_PAID: ";
    out << ms->getFee2Paid() << "\n";
    out << "SESSION_FEE_FAMILY_PAID: ";
    out << ms->getFeeFamilyPaid() << "\n";
    out << "SESSION_FEE_OTHER_PAID: ";
    out << ms->getFeeOtherPaid() << "\n";
    out << "SESSION_INCOME1: ";
    out << ms->getIncomeFee1() << "\n";
    out << "SESSION_INCOME2: ";
    out << ms->getIncomeFee2() << "\n";
    out << "SESSION_INCOME_FAMILY: ";
    out << ms->getIncomeFeeFamily() << "\n";
    out << "SESSION_INCOME_OTHER: ";
    out << ms->getIncomeFeeOther() << "\n";
    out << "SESSION_MEDIATOR_1: ";
    out << ms->getMediator1() << "\n";
    out << "SESSION_MEDIATOR_2: ";
    out << ms->getMediator2() << "\n";
    out << "SESSION_OBSERVER_1: ";
    out << ms->getObserver1() << "\n";
    out << "SESSION_OBSERVER_2: ";
    out << ms->getObserver2() << "\n";
}

void MPFileMaker::parseProcessNotes(QTextStream &out, MediationNotesVector *notes)
{
    out << "NUMBER_OF_NOTES: ";
    out << (int)notes->size() << "\n";
    for(int i = 0; i < (int)notes->size(); i++)
    {
        parseNote(out,notes->at(i));
    }
}

MediationNotesVector MPFileMaker::processNotesParse(QTextStream &in)
{
    QString line;
    MediationNotesVector temp;
    line = in.readLine();
    int numberOFNotes;
    removeMPKeyword(line);
    numberOFNotes = line.toInt();
    for(int i = 0; i < numberOFNotes; i++)
    {
        temp.push_back(noteParse(in));
    }
    return temp;
}

Note *MPFileMaker::noteParse(QTextStream &in)
{
    QString line;
    int sID, mID;
    QString mess;
    Note *temp = new Note();

    line = in.readLine();
    removeMPKeyword(line);
    sID = line.toInt();
    line = in.readLine();
    removeMPKeyword(line);
    mID = line.toInt();
    line = in.readLine();
    removeMPKeyword(line);
    mess = line;

    temp->SetId(sID);
    temp->SetMediationId(mID);
    temp->SetMessage(mess);

    return temp;
}

void MPFileMaker::parseNote(QTextStream &out, Note *note)
{
    out << "NOTE_SESSION_ID: ";
    out << note->GetSessionId() << "\n";
    out << "NOTE_MEDIATION_ID: ";
    out << note->GetmediationId() << "\n";
    out << "NOTE_MESSAGE: ";
    out << note->GetMessage() << "\n";
}
PartyVector MPFileMaker::partiesVectorParse(QTextStream &in)
{
    QString line;
    PartyVector temp;
    line = in.readLine();
    int numberOfParties;
    removeMPKeyword(line);
    numberOfParties = line.toInt();


    for(int i = 0; i < numberOfParties; i++)
    {
        temp.push_back(partyParse(in));
    }

    return temp;
}

void MPFileMaker::parsePartiesVector(QTextStream &out, PartyVector *parties)
{
    out << "NUMBER_OF_PARTIES: ";
    out << (int)parties->size() << "\n";
    for(int i = 0; i < (int)parties->size(); i++)
    {
        parseParty(out,parties->at(i));
    }
}
Party *MPFileMaker::partyParse(QTextStream &in)
{
    Party *temp = new Party();
    temp->SetPrimary(personParse(in));

    return temp;
}

void MPFileMaker::parseParty(QTextStream &out, Party *&party)
{
    parsePerson(out,party->GetPrimary());
}

Person *MPFileMaker::personParse(QTextStream &in)
{
    QString line;
    Person *temp = new Person();
    QString first, middle, last, street, unit, city, county, state, zip, email, atty, pPhone, pPhoneEx, sPhone, sPhoneEx, assPhone, assPhoneEx;
    uint nInHouse;
    first = in.readLine();
    removeMPKeyword(first);
    middle = in.readLine();
    removeMPKeyword(middle);
    last = in.readLine();
    removeMPKeyword(last);
    street = in.readLine();
    removeMPKeyword(street);
    unit = in.readLine();
    removeMPKeyword(unit);
    city = in.readLine();
    removeMPKeyword(city);
    county = in.readLine();
    removeMPKeyword(county);
    state = in.readLine();
    removeMPKeyword(state);
    zip = in.readLine();
    removeMPKeyword(zip);

    line = in.readLine();
    removeMPKeyword(line);
    nInHouse = line.toInt();

    email = in.readLine();
    removeMPKeyword(email);
    atty = in.readLine();
    removeMPKeyword(atty);
    pPhone = in.readLine();
    removeMPKeyword(pPhone);
    pPhoneEx = in.readLine();
    removeMPKeyword(pPhoneEx);
    sPhone = in.readLine();
    removeMPKeyword(sPhone);
    sPhoneEx = in.readLine();
    removeMPKeyword(sPhoneEx);
    assPhone = in.readLine();
    removeMPKeyword(assPhone);
    assPhoneEx = in.readLine();
    removeMPKeyword(assPhoneEx);

    temp->setAssistantPhone(assPhone);
    temp->setAssistantPhoneExt(assPhoneEx);
    temp->setAttorney(atty);
    temp->setCity(city);
    temp->setCounty(county);
    temp->setEmail(email);
    temp->setName(first, middle, last);
    temp->setNumberInHousehold(nInHouse);
    temp->setPrimaryPhone(pPhone);
    temp->setPrimaryPhoneExt(pPhoneEx);
    temp->setSecondaryPhone(sPhone);
    temp->setSecondaryPhoneExt(sPhoneEx);
    temp->setState(state);
    temp->setStreet(street);
    temp->setUnit(unit);
    temp->setZip(zip);

    return temp;
}

void MPFileMaker::parsePerson(QTextStream &out, Person *person)
{
    out << "PERSON_FIRST_NAME: ";
    out << person->getFirstName() << "\n";
    out << "PERSON_MIDDLE_NAME: ";
    out << person->getMiddleName() << "\n";
    out << "PERSON_LAST_NAME: ";
    out << person->getLastName() << "\n";
    out << "PERSON_STREET: ";
    out << person->getStreet() << "\n";
    out << "PERSON_UNIT: ";
    out << person->getUnit() << "\n";
    out << "PERSON_CITY: ";
    out << person->getCity() << "\n";
    out << "PERSON_COUNTY: ";
    out << person->getCounty() << "\n";
    out << "PERSON_STATE: ";
    out << person->getState() << "\n";
    out << "PERSON_ZIP: ";
    out << person->getZip() << "\n";
    out << "PERSON_NUMBER_IN_HOUSE_HOLD: ";
    out << person->getNumberInHousehold() << "\n";
    out << "PERSON_EMAIL: ";
    out << person->getEmail() << "\n";
    out << "PERSON_ATTORNEY: ";
    out << person->getAttorney() << "\n";
    out << "PERSON_PRIMARY_PHONE: ";
    out << person->getPrimaryPhone() << "\n";
    out << "PERSON_PRIMARY_PHONE_EXT: ";
    out << person->getPrimaryPhoneExt() << "\n";
    out << "PERSON_SECONDARY_PHONE_EXT: ";
    out << person->getSecondaryPhone() << "\n";
    out << "PERSON_SECONDARY_PHONE_EXT: ";
    out << person->getSecondaryPhoneExt() << "\n";
    out << "PERSON_ASSISTANT_PHONE: ";
    out << person->getAssistantPhone() << "\n";
    out << "PERSON_ASSISTANT_PHONE: ";
    out << person->getAssistantPhoneExt() << "\n";
}

void MPFileMaker::setFileName(QString fileName)
{
    FileName = fileName;
}


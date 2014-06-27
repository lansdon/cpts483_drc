#include "mpfilemaker.h"

MPFileMaker::MPFileMaker()
{
    mpVector = new MediationProcessVector();
    FileName = "test.mp";
}

void MPFileMaker::addMP(MediationProcess *mp)
{
    mpVector->push_back(mp);
}

void MPFileMaker::sendToFile()
{
    QFile file(FileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream fileStream(&file);
        parseToFile(fileStream);
        file.close();
    }
    else
        qDebug() << "error opening file.";

}

void MPFileMaker::sendToFile(MediationProcessVector *MPVector)
{
    mpVector = MPVector;
    sendToFile();
}

void MPFileMaker::sendToFile(MediationProcess *MP)
{
    mpVector->push_back(MP);
    sendToFile();
}

void MPFileMaker::getFromFile()
{
    //file to parse
    QFile file(FileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream fileStream(&file);
        fileToParse(fileStream);
        file.close();
    }
    else
        qDebug() << "error opening file.";
}

void MPFileMaker::fileToParse(QDataStream &in)
{
    int numberOfMPs;
    //MediationProcess *temp;
    in >> numberOfMPs;
    mpVector->clear();
    for(int i = 0; i < numberOfMPs; i++)
    {

        mpVector->push_back(fileToProcessParse(in));
    }
}

void MPFileMaker::parseToFile(QDataStream &out)
{
    out << (int)mpVector->size();
    for(int i = 0; i < mpVector->size();i++)
    {
        parseProcessToFile(out,mpVector->at(i));
    }
}
MediationProcess *MPFileMaker::fileToProcessParse(QDataStream &in)
{
    MediationProcess *temp;
    unsigned int id;
    QDateTime creation, updated, mediationCreationDate;
    uint state, activeState;
    CountyIds countyid;
    DisputeTypes disType;
    ReferralTypes reftype;
    bool spanish;
    DisputeProcessStates currState;
    PartyVector parties;
    MediationNotesVector notes;
    MediationSessionVector sessions;
    in >> id;
    in >> creation;
    in >> updated;
    in >> state;
    in >> activeState;
    in >> mediationCreationDate;
    in >> (qint32&)countyid;
    in >> (qint32&)disType;
    in >> (qint32&)reftype;
    in >> spanish;
    in >> (qint32&)currState;
    parties = partiesVectorParse(in);
    notes = processNotesParse(in);
    sessions = sessionsVectorParse(in);
    temp = new MediationProcess(parties, state, activeState, disType, mediationCreationDate, currState, countyid, notes, reftype, spanish, sessions);
    temp->SetId(id);
    temp->SetCreatedDate(creation);
    temp->SetUpdatedDate(updated);


    return temp;
}

void MPFileMaker::parseProcessToFile(QDataStream &out, MediationProcess *mp)
{
    out << mp->GetId();
    out << mp->GetCreatedDate();
    out << mp->GetUpdated();
    out << mp->getStateTransition();
    out << mp->getActiveStateTransition();
    out << mp->GetCreationDate();
    out << mp->GetCountyId();
    out << mp->GetDisputeType();
    out << mp->GetReferralType();
    out << mp->GetRequiresSpanish();
    out << mp->GetCurrentState();
    parsePartiesVector(out,mp->GetParties());
    parseProcessNotes(out, mp->GetNotes());
    parseSessionsVector(out, mp->getMediationSessionVector());

}

void MPFileMaker::parseSessionsVector(QDataStream &out, MediationSessionVector *msv)
{
    out << (int)msv->size();
    for(int i = 0; i < msv->size(); i++)
    {
        parseSession(out,msv->at(i));
    }
}

MediationSessionVector MPFileMaker::sessionsVectorParse(QDataStream &in)
{
    int numberOfSessions;
    in >> numberOfSessions;
    MediationSessionVector temp;
    for(int i = 0; i < numberOfSessions; i++)
    {
        temp.push_back(sessionParse(in));
    }

    return temp;
}

MediationSession *MPFileMaker::sessionParse(QDataStream &in)
{
    MediationSession *temp = new MediationSession();
    QDateTime create, time;
    SessionStates state;
    QString fee1, fee2, fee3, fee4, income1, income2, income3, income4;
    bool paid1, paid2, paid3, paid4;
    Person *med1, *med2, *obs1, *obs2;
    in >> (qint32&)state;
    in >> create;
    in >> time;
    in >> fee1;
    in >> fee2;
    in >> fee3;
    in >> fee4;
    in >> paid1;
    in >> paid2;
    in >> paid3;
    in >> paid4;
    in >> income1;
    in >> income2;
    in >> income3;
    in >> income4;
    med1 = personParse(in);
    med2 = personParse(in);
    obs1 = personParse(in);
    obs2 = personParse(in);

    temp->SetState(state);
    temp->setMediationTime(time);
    temp->setMediationCreate(create);
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
    temp->setIncomeFeeOther(income4);
    temp->setMediator1(med1);
    temp->setMediator2(med2);
    temp->setObserver1(obs1);
    temp->setObserver2(obs2);


    return temp;
}

void MPFileMaker::parseSession(QDataStream &out, MediationSession *ms)
{
    out << ms->GetState();
    out << ms->getMediationCreation();
    out << ms->getMediationTime();
    out << ms->getFee1();
    out << ms->getFee2();
    out << ms->getFeeFamily();
    out << ms->getFeeOther();
    out << ms->getFee1Paid();
    out << ms->getFee2Paid();
    out << ms->getFeeFamilyPaid();
    out << ms->getFeeOtherPaid();
    out << ms->getIncomeFee1();
    out << ms->getIncomeFee2();
    out << ms->getIncomeFeeFamily();
    out << ms->getIncomeFeeOther();
    parsePerson(out,ms->getMediator1());
    parsePerson(out,ms->getMediator2());
    parsePerson(out,ms->getObserver1());
    parsePerson(out, ms->getObserver2());
}

void MPFileMaker::parseProcessNotes(QDataStream &out, MediationNotesVector *notes)
{
    out << (int)notes->size();
    for(int i = 0; i < notes->size(); i++)
    {
        parseNote(out,notes->at(i));
    }
}

MediationNotesVector MPFileMaker::processNotesParse(QDataStream &in)
{
    int numberOFNotes;
    MediationNotesVector temp;
    in >> numberOFNotes;
    for(int i = 0; i < numberOFNotes; i++)
    {
        temp.push_back(noteParse(in));
    }
    return temp;
}

Note *MPFileMaker::noteParse(QDataStream &in)
{
    int sID, mID;
    QString mess;
    Note *temp = new Note();
    in >> sID;
    in >> mID;
    in >> mess;
    temp->SetId(sID);
    temp->SetMediationId(mID);
    temp->SetMessage(mess);

    return temp;
}

void MPFileMaker::parseNote(QDataStream &out, Note *note)
{
    out << note->GetSessionId();
    out << note->GetmediationId();
    out << note->GetMessage();
}
PartyVector MPFileMaker::partiesVectorParse(QDataStream &in)
{
    int numberOfParties;
    in >> numberOfParties;
    PartyVector temp;

    for(int i = 0; i < numberOfParties; i++)
    {
        temp.push_back(partyParse(in));
    }

    return temp;
}

void MPFileMaker::parsePartiesVector(QDataStream &out, PartyVector *parties)
{
    out << (int)parties->size();
    for(int i = 0; i < parties->size(); i++)
    {
        parseParty(out,parties->at(i));
    }
}
Party *MPFileMaker::partyParse(QDataStream &in)
{
    Party *temp = new Party();
    temp->SetPrimary(personParse(in));

    return temp;
}

void MPFileMaker::parseParty(QDataStream &out, Party *&party)
{
    parsePerson(out,party->GetPrimary());
}

Person *MPFileMaker::personParse(QDataStream &in)
{
    Person *temp = new Person();
    QString first, middle, last, street, unit, city, county, state, zip, email, atty, pPhone, pPhoneEx, sPhone, sPhoneEx, assPhone, assPhoneEx;
    uint nInHouse;
    in >> first;
    in >> middle;
    in >> last;
    in >> street;
    in >> unit;
    in >> city;
    in >> county;
    in >> state;
    in >> zip;
    in >> nInHouse;
    in >> email;
    in >> atty;
    in >> pPhone;
    in >> pPhoneEx;
    in >> sPhone;
    in >> sPhoneEx;
    in >> assPhone;
    in >> assPhoneEx;

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

void MPFileMaker::parsePerson(QDataStream &out, Person *person)
{
    out << person->getFirstName();
    out << person->getMiddleName();
    out << person->getLastName();
    out << person->getStreet();
    out << person->getUnit();
    out << person->getCity();
    out << person->getCounty();
    out << person->getState();
    out << person->getZip();
    out << person->getNumberInHousehold();
    out << person->getEmail();
    out << person->getAttorney();
    out << person->getPrimaryPhone();
    out << person->getPrimaryPhoneExt();
    out << person->getSecondaryPhone();
    out << person->getSecondaryPhoneExt();
    out << person->getAssistantPhone();
    out << person->getAssistantPhoneExt();
}

void MPFileMaker::setFileName(QString fileName)
{
    FileName = fileName;
}

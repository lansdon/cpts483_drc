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

}

void MPFileMaker::parseToFile(QDataStream &out)
{
    out << (int)mpVector->size();
    for(int i = 0; i < mpVector->size();i++)
    {
        parseProcessToFile(out,mpVector->at(i));
    }
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
    for(int i = 0; i < notes->size(); i++)
    {
        parseNote(out,notes->at(i));
    }
}

void MPFileMaker::parseNote(QDataStream &out, Note *note)
{
    out << note->GetSessionId();
    out << note->GetmediationId();
    out << note->GetMessage();
}

void MPFileMaker::parsePartiesVector(QDataStream &out, PartyVector *parties)
{
    out << (int)parties->size();
    for(int i = 0; i < parties->size(); i++)
    {
        parseParty(out,parties->at(i));
    }
}

void MPFileMaker::parseParty(QDataStream &out, Party *&party)
{
    parsePerson(out,party->GetPrimary());
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

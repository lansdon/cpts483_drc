#ifndef MPFILEMAKER_H
#define MPFILEMAKER_H

/// Qt stuff
#include <QDataStream>
#include <QString>
#include <QDebug>
#include <QFile>

/// drc stuff
#include "drctypes.h"
#include "DRCModels.h"

class MPFileMaker
{
public:
    MPFileMaker();
    void addMP(MediationProcess *mp);
    void sendToFile();
    void sendToFile(MediationProcessVector *MPVector);
    void sendToFile(MediationProcess *MP);
    void getFromFile();
    void getFromFile(QString fileName);
    void fileToParse(QDataStream &in);
    void parseToFile(QDataStream &out);
    void setFileName(QString fileName);
    MediationProcess *fileToProcessParse(QDataStream &in);
    void parseProcessToFile(QDataStream &out, MediationProcess *mp);
    PartyVector partiesVectorParse(QDataStream &in);
    void parsePartiesVector(QDataStream &out, PartyVector *parties);
    Party *partyParse(QDataStream &in);
    void parseParty(QDataStream &out, Party *&party);
    Person *personParse(QDataStream &in);
    void parsePerson(QDataStream &out, Person *person);
    MediationNotesVector processNotesParse(QDataStream &in);
    void parseProcessNotes(QDataStream &out, MediationNotesVector *notes);
    MediationSessionVector sessionsVectorParse(QDataStream &in);
    void parseSessionsVector(QDataStream &out, MediationSessionVector *msv);
    MediationSession *sessionParse(QDataStream &in);
    void parseSession(QDataStream &out, MediationSession *ms);
    Note *noteParse(QDataStream &in);
    void parseNote(QDataStream &out, Note *note);

private:
    MediationProcessVector *mpVector;
    QString FileName;

};

#endif // MPFILEMAKER_H

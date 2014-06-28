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
    void fileToParse(QTextStream &in);
    void parseToFile(QTextStream &out);
    void setFileName(QString fileName);
    MediationProcess *fileToProcessParse(QTextStream &in);
    void parseProcessToFile(QTextStream &out, MediationProcess *mp);
    PartyVector partiesVectorParse(QTextStream &in);
    void parsePartiesVector(QTextStream &out, PartyVector *parties);
    Party *partyParse(QTextStream &in);
    void parseParty(QTextStream &out, Party *&party);
    Person *personParse(QTextStream &in);
    void parsePerson(QTextStream &out, Person *person);
    MediationNotesVector processNotesParse(QTextStream &in);
    void parseProcessNotes(QTextStream &out, MediationNotesVector *notes);
    MediationSessionVector sessionsVectorParse(QTextStream &in);
    void parseSessionsVector(QTextStream &out, MediationSessionVector *msv);
    MediationSession *sessionParse(QTextStream &in);
    void parseSession(QTextStream &out, MediationSession *ms);
    Note *noteParse(QTextStream &in);
    void parseNote(QTextStream &out, Note *note);
    MediationProcessVector *getMedationProcessVector() const;

private:
    MediationProcessVector *mpVector;
    QString FileName;
    QString empty;
    void removeMPKeyword(QString &value);

};

#endif // MPFILEMAKER_H

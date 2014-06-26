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
    //MediationProcessVector *getFromFile(QString fileName);
    void parseToFile(QDataStream &out);
    void setFileName(QString fileName);
    void parseProcessToFile(QDataStream &out, MediationProcess *mp);
    void parsePartiesVector(QDataStream &out, PartyVector *parties);
    void parseParty(QDataStream &out, Party *&party);
    void parsePerson(QDataStream &out, Person *person);
    void parseProcessNotes(QDataStream &out, MediationNotesVector *notes);
    void parseSessionsVector(QDataStream &out, MediationSessionVector *msv);
    void parseSession(QDataStream &out, MediationSession *ms);
    void parseNote(QDataStream &out, Note *note);

private:
    MediationProcessVector *mpVector;
    QString FileName;

};

#endif // MPFILEMAKER_H

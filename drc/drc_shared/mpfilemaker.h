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

/*!
 * \brief The MPFileMaker class
 */
class MPFileMaker
{
public:
    MPFileMaker();
    /*!
     * \brief addMP
     * \param mp
     */
    void addMP(MediationProcess *mp);
    /*!
     * \brief sendToFile
     */
    void sendToFile();
    /*!
     * \brief sendToFile
     * \param MPVector
     */
    void sendToFile(MediationProcessVector *MPVector);
    /*!
     * \brief sendToFile
     * \param MP
     */
    void sendToFile(MediationProcess *MP);
    /*!
     * \brief getFromFile
     */
    void getFromFile();
    /*!
     * \brief getFromFile
     * \param fileName
     */
    void getFromFile(QString fileName);
    /*!
     * \brief fileToParse
     * \param in
     */
    void fileToParse(QTextStream &in);
    /*!
     * \brief parseToFile
     * \param out
     */
    void parseToFile(QTextStream &out);
    /*!
     * \brief setFileName
     * \param fileName
     */
    void setFileName(QString fileName);
    /*!
     * \brief fileToProcessParse
     * \param in
     * \return
     */
    MediationProcess *fileToProcessParse(QTextStream &in);
    /*!
     * \brief parseProcessToFile
     * \param out
     * \param mp
     */
    void parseProcessToFile(QTextStream &out, MediationProcess *mp);
    /*!
     * \brief partiesVectorParse
     * \param in
     * \return
     */
    PartyVector partiesVectorParse(QTextStream &in);
    /*!
     * \brief parsePartiesVector
     * \param out
     * \param parties
     */
    void parsePartiesVector(QTextStream &out, PartyVector *parties);
    /*!
     * \brief partyParse
     * \param in
     * \return
     */
    Party *partyParse(QTextStream &in);
    /*!
     * \brief parseParty
     * \param out
     * \param party
     */
    void parseParty(QTextStream &out, Party *&party);
    /*!
     * \brief personParse
     * \param in
     * \return
     */
    Person *personParse(QTextStream &in);
    /*!
     * \brief parsePerson
     * \param out
     * \param person
     */
    void parsePerson(QTextStream &out, Person *person);
    /*!
     * \brief processNotesParse
     * \param in
     * \return
     */
    MediationNotesVector processNotesParse(QTextStream &in);
    /*!
     * \brief parseProcessNotes
     * \param out
     * \param notes
     */
    void parseProcessNotes(QTextStream &out, MediationNotesVector *notes);
    /*!
     * \brief sessionsVectorParse
     * \param in
     * \return
     */
    MediationSessionVector sessionsVectorParse(QTextStream &in);
    /*!
     * \brief parseSessionsVector
     * \param out
     * \param msv
     */
    void parseSessionsVector(QTextStream &out, MediationSessionVector *msv);
    /*!
     * \brief sessionParse
     * \param in
     * \return
     */
    MediationSession *sessionParse(QTextStream &in);
    /*!
     * \brief parseSession
     * \param out
     * \param ms
     */
    void parseSession(QTextStream &out, MediationSession *ms);
    /*!
     * \brief noteParse
     * \param in
     * \return
     */
    Note *noteParse(QTextStream &in);
    /*!
     * \brief parseNote
     * \param out
     * \param note
     */
    void parseNote(QTextStream &out, Note *note);
    /*!
     * \brief getMedationProcessVector
     * \return
     */
    MediationProcessVector *getMedationProcessVector() const;

private:
    MediationProcessVector *mpVector;
    QString FileName;
    QString empty;
    /*!
     * \brief removeMPKeyword
     * \param value
     */
    void removeMPKeyword(QString &value);

};

#endif // MPFILEMAKER_H

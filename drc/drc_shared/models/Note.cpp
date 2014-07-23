#include "Note.h"

Note::Note(QString message)
: DBBaseObject()
, _message(message)
, _sessionId(0)
, _mediationId(0)
{

}

void Note::BuildToPDF(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    QString Note = m_created.toString();
    Note += "\t\t";
    Note += _message;
    Note += "\n";
    cursor.insertText(Note, _tableTextFormat);
}

void Note::SetMessage(QString message)
{
    _message = message;
}

void Note::SetSessionId(int sessionId)
{
    _sessionId = sessionId;
}

void Note::SetMediationId(int mediationId)
{
    _mediationId = mediationId;
}

QString Note::GetMessage()
{
    return _message;
}

int Note::GetmediationId()
{
    return _mediationId;
}

int Note::GetSessionId()
{
    return _sessionId;
}

// Abstract Overrides
QString Note::Parse()
{

    QString toReturn;

    toReturn += QString("%1, %2, ").arg(QString::number(this->GetmediationId()))
                                   .arg(QString::number(this->GetSessionId()));

    toReturn += QString("'%1', ").arg(this->GetMessage().replace("'", "''"));

    toReturn += QString("'%1' ").arg(this->GetCreatedDate().toString("yyyy-MM-dd hh:mm:ss"));

    return toReturn;
}

QString Note::UpdateParse()
{

    return QString("Note = '%1'").arg(this->GetMessage().replace("'", "''"));

}

QString Note::GetIdRowName()
{
    return QString("Note_id");
}

QString Note::table()
{
    return "Notes_Table";
}

QString Note::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!
    return "";
}

QString Note::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!
    return "";
}

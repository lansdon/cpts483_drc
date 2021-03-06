#include "Note.h"

Note::Note(QString message)
: DBBaseObject()
, _message(message)
, _sessionId(0)
, _mediationId(0)
{
    _headerFormat.setFontPointSize(12);
    _tableTextFormat.setFontPointSize(10);
    _tableCellBlue.setBackground(QColor("#C2E0FF"));
    _tableIndexDark.setBackground(QColor("#e0e0e0"));
    _tableIndexLight.setBackground(QColor("#eeeee0"));

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

QString Note::ColumnNames()
{
    return "";
}

// Abstract Overrides
QString Note::Parse()
{

    QString toReturn;

    toReturn += QString("null, ");

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
    return "";
}

QString Note::SearchQuery()
{
    return "";
}

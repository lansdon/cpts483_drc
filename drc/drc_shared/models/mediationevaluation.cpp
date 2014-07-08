#include "mediationevaluation.h"

MediationEvaluation::MediationEvaluation()
{
    _q1 = 0;
    _q2 = _q3 = _q4 = _q5 = _q6 = _q7 = _q8 = _callBackPermissions = _promoPermissions = NO_ANSWER;
}

QString MediationEvaluation::Parse()
{
    QString toReturn;

    if(_q3 == YES)
    {
        toReturn += "1, 0, 0, ";
    }
    else if(_q3 == NO)
    {
        toReturn += "0, 1, 0, ";
    }
    else if(_q3 == SOMEWHAT)
    {
        toReturn += "0, 0, 1, ";
    }

    if(_q4 == YES)
    {
        toReturn += "1, 0, 0, ";
    }
    else if(_q4 == NO)
    {
        toReturn += "0, 1, 0, ";
    }
    else if(_q4 == SOMEWHAT)
    {
        toReturn += "0, 0, 1, ";
    }

    if(_q5 == YES)
    {
        toReturn += "1, 0, 0, ";
    }
    else if(_q5 == NO)
    {
        toReturn += "0, 1, 0, ";
    }
    else if(_q5 == SOMEWHAT)
    {
        toReturn += "0, 0, 1, ";
    }

    if(_q6 == YES)
    {
        toReturn += "1, 0, 0, ";
    }
    else if(_q6 == NO)
    {
        toReturn += "0, 1, 0, ";
    }
    else if(_q6 == SOMEWHAT)
    {
        toReturn += "0, 0, 1, ";
    }

    if(_q7 == YES)
    {
        toReturn += "1, 0, 0, ";
    }
    else if(_q7 == NO)
    {
        toReturn += "0, 1, 0, ";
    }
    else if(_q7 == SOMEWHAT)
    {
        toReturn += "0, 0, 1, ";
    }

    if(_q8 == YES)
    {
        toReturn += "1, 0, 0";
    }
    else if(_q8 == NO)
    {
        toReturn += "0, 1, 0";
    }
    else if(_q8 == SOMEWHAT)
    {
        toReturn += "0, 0, 1";
    }

}

QString MediationEvaluation::UpdateParse()
{
#warning TODO - UpdateParse() UNIMPLEMENTED!!!!
    return "";

}

QString MediationEvaluation::table()
{
#warning TODO - table() UNIMPLEMENTED!!!!
    return "Evaluation_Table";

}

QString MediationEvaluation::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!
    return "";

}

QString MediationEvaluation::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!
    return "";

}

QString MediationEvaluation::GetIdRowName()
{
#warning TODO - GetIdRowName() UNIMPLEMENTED!!!!
    return "";
}

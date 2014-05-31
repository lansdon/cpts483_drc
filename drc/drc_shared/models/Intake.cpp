#include "Intake.h"

Intake::Intake()
{
    claimant = Person("");

}

void Intake::addClaimant(QString input)
{
    Person temp(input);
    claimant = temp;
}

void Intake::addRespondents(QString input)
{
    Person temp(input);
    respondents.push_back(temp);
}

time_t Intake::getTime() const
{
    return enterTime;
}

void Intake::setTime(time_t t)
{
    enterTime = t;
}

Person Intake::getClaimant() const
{
    return claimant;
}


int Intake::getNumberOfPeople() const
{
    return respondents.size();
}


std::vector<Person> Intake::getRespondents() const
{
    return respondents;
}



#include "Intake.h"

Intake::Intake()
{
    claimant = Person("");

}

void Intake::addClaimant(Person input)
{
    claimant = input;
}

void Intake::addRespondents(Person input)
{
    respondents.push_back(input);
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



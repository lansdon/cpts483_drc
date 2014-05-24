#include "IntakeForm.h"

IntakeForm::IntakeForm()
{
}

void IntakeForm::populate(QString input)
{
    Person temp(input);

    clients.push_back(temp);
}

void IntakeForm::setTime(time_t t)
{
    enterTime = t;
}

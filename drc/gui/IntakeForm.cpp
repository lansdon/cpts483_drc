#include "IntakeForm.h"

IntakeForm::IntakeForm()
{

}

void IntakeForm::addPerson(QString input)
{
    Person temp(input);

    clients.push_back(temp);
}

void IntakeForm::setTime(time_t t)
{
    enterTime = t;
}

Person IntakeForm::getPerson(std::string n)
{
    for(unsigned long i = 0;i<clients.size();i++)
    {
        if(clients[i].getName()==n)
        {
            return clients[i];
        }
    }
    return Person("none");
}



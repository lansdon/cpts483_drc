#include "Intake.h"

Intake::Intake()
{

}

void Intake::addPerson(QString input)
{
    Person temp(input);

    clients.push_back(temp);
}

void Intake::setTime(time_t t)
{
    enterTime = t;
}

Person Intake::getPerson(std::string n)
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



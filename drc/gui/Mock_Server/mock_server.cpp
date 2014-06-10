#include "mock_server.h"
#include <qdebug.h>
#include <ctime>

Mock_Server::Mock_Server()
{
    Mediator::Register(MKEY_GUI_QUERY_PERSON, [this](MediatorArg arg){SendResults(arg); });
    Mediator::Register(MKEY_GUI_QUERY_MEDIATION, [this](MediatorArg arg){SendResultsMediation(arg); });
}
void Mock_Server::PrintPerson(Person *input, std::fstream &file)
{
    time_t tm = std::time(0);
    //std::time(&tm);
    file.open("test.out",std::fstream::out | std::fstream::app);
    if(file.is_open())
    {
        file << "Test from Person querry\n";
        file << "Time tested: " << std::ctime(&tm);
        file << "Test data(Full Name): " << input->FullName().toUtf8().constData() <<std::endl;
        file << "Test data(get state): " << input->getState()<<std::endl<<std::endl;
        file << "------------------------------------------------------------------"<<std::endl<<std::endl;
        file.close();
    }
    else
    {
        qDebug() << "File test.out couldn't be opened";
    }
}
void Mock_Server::PrintMediationProcess(MediationProcess *input, std::fstream &file)
{
    time_t tm = std::time(0);
    //std::time(&tm);
    file.open("test.out",std::fstream::out | std::fstream::app);
    if(file.is_open())
    {
        file << "Test from mediation process querry\n";
        file << "Time tested: " << std::ctime(&tm);
        file << "Test data(Primary party Full Name): " << input->GetParty1()->GetPrimary().FullName().toUtf8().constData() <<std::endl;
        file << "Test data(Attorny full name): " << input->GetParty2()->GetAttorney().FullName().toUtf8().constData() <<std::endl<<std::endl;
        file << "------------------------------------------------------------------"<<std::endl<<std::endl;
        file.close();
    }
    else
    {
        qDebug() << "File test.out couldn't be opened";
    }
}
void Mock_Server::SendResults(MediatorArg Myarg)
{
    Person *recieved = Myarg.getArg<Person *>();
    std::fstream infile;
    PrintPerson(recieved, infile);
    for(int i = 0; i < 20; i++)
    {
        Person *temp = Person::SampleData();
        _personVector.push_back(temp);
    }
    Mediator::Call(MKEY_DB_QUERY_PERSON,&_personVector);
}

void Mock_Server::SendResultsMediation(MediatorArg arg)
{
    MediationProcess *recieved = arg.getArg<MediationProcess *>();
    std::fstream infile;
    PrintMediationProcess(recieved, infile);
    for(int i = 0; i< 20; i++)
    {
        MediationProcess *temp = MediationProcess::SampleData();
        _mediationProcessVector.push_back(temp);
    }
    Mediator::Call(MKEY_DB_QUERY_MEDIATION,&_mediationProcessVector);
}

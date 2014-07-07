#include "Mediator.h"
#include "MediatorArg.h"
#include <QDebug>

//namespace drc {
//namespace drc_shared {


Mediator& Mediator::Instance()
{
	static Mediator instance;
	return instance;
}

MediatorId Mediator::Register(QString key, MediatorCallback* callback)
{
    Instance()._mediatorMap[key].push_back(callback);
    QString dbug = "Mediator Register -> Key:" + key + "   id: " + QString::number(callback->GetId());
    qDebug() << dbug;
    return callback->GetId();
}

MediatorId Mediator::Register(QString key, MediatorCallbackFunc function)
{
    return Register(key, new MediatorCallback(function));
}

void Mediator::Unregister(QString key, MediatorId callbackId)
{
    if (Instance()._mediatorMap.count(key) != 0)
    {
        MediatorCallbackVector& vec = Instance()._mediatorMap[key];

        auto found = std::find_if( vec.begin(), vec.end(), [callbackId] (MediatorCallback* lhs) { return lhs->GetId() == callbackId;} );
        if(found != vec.end())
        {
            qDebug() << QString("Mediator Unregister -> Key:" + key + "   id: " + QString::number((*found)->GetId()));
            vec.erase(found);
        }
        else
        {
            qDebug() << QString("Mediator Unregister - NO MATCH -> Key:" + key);
        }

        // Remove the key from the map entirely if not used.
        if (vec.size() == 0)
        {
            Instance()._mediatorMap.erase(Instance()._mediatorMap.find(key));
        }
    }

    PrintState();
}

// Call Override to package arguments into a MediatorArg
void Mediator::Call(QString key, void* object, bool success, QString errorMessage)
{
	Call(key, MediatorArg(object, success, errorMessage));
}

void Mediator::Call(QString key, MediatorArg arg)
{
    qDebug() << "------  Medaitor Call: " << key << " (" << Instance()._mediatorMap.count(key) << ")";
    if (Instance()._mediatorMap.count(key) != 0)
	{
        for (MediatorCallbackVector::iterator it = Instance()._mediatorMap[key].begin();
            it != Instance()._mediatorMap[key].end();
            ++it)
		{
            QString ptrValue = (*it)->toString();
            qDebug() << "  -> " << ptrValue;
            if(*it)
                (*it)->Run(arg);
		}
	}
}

void Mediator::Clear()
{
    Instance()._mediatorMap.clear();
}

// Print a list of registered callbacks
void Mediator::PrintState()
{
    qDebug() << "\n---------------- Mediator Callbacks ----------------";
    foreach(auto callbackPair, Instance()._mediatorMap)
    {
        qDebug() << "\n_______" << callbackPair.first;
        foreach(MediatorCallback* cb, callbackPair.second)
        {
            qDebug() << "\t  id:" + QString::number( cb->GetId() ) + " = " + cb->toString();
        }

    }
    qDebug() << "--------------------------------\n";
}

//}
//}

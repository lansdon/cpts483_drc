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
    Instance().MediatorMap[key].push_back(callback);
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
    if (Instance().MediatorMap.count(key) != 0)
    {
        auto vec = Instance().MediatorMap[key];
        auto found = std::find_if( vec.begin(), vec.end(), [callbackId] (MediatorCallback* lhs) { return lhs->GetId() == callbackId;} );
        if(found != vec.end())
            qDebug() << QString("Mediator Unregister -> Key:" + key + "   id: " + QString::number((*found)->GetId()));
        else qDebug() << "Mediator Unregister -> NO match!";
        vec.erase(found);

        if (vec.size() == 0)
        {
            Instance().MediatorMap.erase(Instance().MediatorMap.find(key));
        }
    }
 }

// Call Override to package arguments into a MediatorArg
void Mediator::Call(QString key, void* object, bool success, QString errorMessage)
{
	Call(key, MediatorArg(object, success, errorMessage));
}

void Mediator::Call(QString key, MediatorArg arg)
{
    qDebug() << "------  Medaitor Call: " << key;
    if (Instance().MediatorMap.count(key) != 0)
	{
        for (MediatorCallbackVector::iterator it = Instance().MediatorMap[key].begin();
            it != Instance().MediatorMap[key].end();
            ++it)
		{
 //           qDebug() << "  -> " << QString::fromStdString((*it)->toString());
            (*it)->Run(arg);
		}
	}
}

void Mediator::Clear()
{
	Instance().MediatorMap.clear();
}


//}
//}

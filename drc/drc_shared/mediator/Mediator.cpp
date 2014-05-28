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

MediatorId Mediator::Register(std::string Key, MediatorCallback* Callback)
{
    Instance().MediatorMap[Key].push_back(Callback);
    return Callback->GetId();
}

MediatorId Mediator::Register(std::string Key, MediatorCallbackType Function)
{
    return Register(Key, new MediatorCallback(Function));
}

void Mediator::Unregister(std::string Key, MediatorCallback *Function)
{
	if (Instance().MediatorMap.count(Key) != 0)
	{
        auto found = std::find_if(Instance().MediatorMap[Key].begin(),
                             Instance().MediatorMap[Key].end(),
                             [Function] (MediatorCallback* lhs)
                            {
                                qDebug() << lhs << "==" << Function;
                                return lhs == Function;
                            }
        );
        if(found != Instance().MediatorMap[Key].end())
            qDebug() << "Mediator Unregister -> Found match!";
        else qDebug() << "Mediator Unregister -> NO match!";
         Instance().MediatorMap[Key].erase(found);
	}
	if (Instance().MediatorMap[Key].size() == 0)
	{
		Instance().MediatorMap.erase(Instance().MediatorMap.find(Key));
	}
}

void Mediator::Unregister(std::string Key, MediatorId callbackId)
{
    if (Instance().MediatorMap.count(Key) != 0)
    {
        auto found = std::find_if(Instance().MediatorMap[Key].begin(),
                             Instance().MediatorMap[Key].end(),
                             [callbackId] (MediatorCallback* lhs)
                            {
                                qDebug() << lhs->GetId() << "==" << callbackId;
                                return lhs->GetId() == callbackId;
                            }
        );
        if(found != Instance().MediatorMap[Key].end())
            qDebug() << "Mediator Unregister -> Found match!";
        else qDebug() << "Mediator Unregister -> NO match!";
         Instance().MediatorMap[Key].erase(found);
    }
    if (Instance().MediatorMap[Key].size() == 0)
    {
        Instance().MediatorMap.erase(Instance().MediatorMap.find(Key));
    }
}

// Call Override to package arguments into a MediatorArg
void Mediator::Call(std::string key, void* object, bool success, std::string errorMessage)
{
	Call(key, MediatorArg(object, success, errorMessage));
}

void Mediator::Call(std::string Key, MediatorArg Object)
{
	if (Instance().MediatorMap.count(Key) != 0)
	{
        for (std::vector<MediatorCallback*>::iterator It = Instance().MediatorMap[Key].begin();
			It != Instance().MediatorMap[Key].end();
			++It)
		{
            MediatorCallback* c = *It;
            c->Run(Object);
//            (*c)(Object);
		}
	}
}

void Mediator::Clear()
{
	Instance().MediatorMap.clear();
}


//}
//}

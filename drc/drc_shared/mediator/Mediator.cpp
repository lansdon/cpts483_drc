#include "Mediator.h"
#include "MediatorArg.h"


//namespace drc {
//namespace drc_shared {


Mediator& Mediator::Instance()
{
	static Mediator instance;
	return instance;
}

void Mediator::Register(std::string Key, MediatorCallback Function)
{
	Instance().MediatorMap[Key].push_back(Function);
}

void Mediator::Unregister(std::string Key, MediatorCallback Function)
{
	if (Instance().MediatorMap.count(Key) != 0)
	{
//		Instance().MediatorMap[Key].erase(std::find(Instance().MediatorMap[Key].begin(),
//			Instance().MediatorMap[Key].end(),
//			Function));
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
		for (std::vector<MediatorCallback>::iterator It = Instance().MediatorMap[Key].begin();
			It != Instance().MediatorMap[Key].end();
			++It)
		{
			(*It)(Object);
		}
	}
}

void Mediator::Clear()
{
	Instance().MediatorMap.clear();
}


//}
//}

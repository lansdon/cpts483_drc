#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <map>
#include <string>
#include <vector>
#include <functional>

//namespace drc {
//namespace drc_shared {


class MediatorArg;


//typedef void(*MediatorCallback)(MediatorArg);	// Callback function type

typedef std::function<void(MediatorArg mediatorArg)> MediatorCallback;				// Lambda signature

class Mediator
{
private:
	Mediator() {/*Filler!!*/ }

	Mediator(const Mediator&) {/*Filler!!*/ }

	Mediator& operator = (const Mediator&);

	~Mediator() {/*Filler!!*/ }

	static Mediator& Instance();

	std::map<std::string, std::vector<MediatorCallback>> MediatorMap;

public:

	static void Register(std::string Key, MediatorCallback Function);

	static void Unregister(std::string Key, MediatorCallback Function);

	// Call Override to package arguments into a MediatorArg
	static void Call(std::string key, void* object = nullptr, bool success = true, std::string errorMessage = "");

	static void Call(std::string Key, MediatorArg Object);

	static void Clear();
};

//}   // end namespace drc_shared
//}   // end namespace drc

#endif

#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <map>
#include <string>
#include <vector>
#include <functional>
#include "drc_shared/mediator/MediatorArg.h"
//namespace drc {
//namespace drc_shared {


typedef std::function<void(MediatorArg mediatorArg)> MediatorCallbackFunc;				// Lambda signature

// MediatorCallback
// This is a wrapper for MediatorCallbackType that tracks a unique id.
// The caller can use the id to unregister the function at a later date.
typedef unsigned int MediatorId;
static MediatorId __MEDIATOR_UNIQUE_ID = 0;    // used to increment unique ids  (DON'T EDIT THIS!)
class MediatorCallback
{
public:
    MediatorCallback(MediatorCallbackFunc callback) :  _callback(callback) {_id = ++__MEDIATOR_UNIQUE_ID;}
    void Run(MediatorArg &arg) { _callback(arg); }
    unsigned int GetId() { return _id; }
private:
    MediatorId _id;
    MediatorCallbackFunc _callback;
};

class Mediator
{
private:
	Mediator() {/*Filler!!*/ }

	Mediator(const Mediator&) {/*Filler!!*/ }

	Mediator& operator = (const Mediator&);

	~Mediator() {/*Filler!!*/ }

	static Mediator& Instance();

    typedef std::vector<MediatorCallback*> MediatorCallbackVector;
    typedef std::map<std::string, MediatorCallbackVector> MediatorCallbackMap;
    MediatorCallbackMap MediatorMap;

public:

    static MediatorId Register(std::string key, MediatorCallbackFunc function);
    static MediatorId Register(std::string key, MediatorCallback* callback);

    static void Unregister(std::string Key, MediatorId callbackId);

	// Call Override to package arguments into a MediatorArg
	static void Call(std::string key, void* object = nullptr, bool success = true, std::string errorMessage = "");
	static void Call(std::string Key, MediatorArg Object);

	static void Clear();
};

//}   // end namespace drc_shared
//}   // end namespace drc

#endif

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
    std::string toString() { return _callback.target_type().name(); }

private:
    MediatorId _id;
    MediatorCallbackFunc _callback;
};


///
/// \brief The Mediator class
///
/// This is the primary class for registering to listen for events and signaling events.
/// A listener will register a callback function that is fired whenever the event (key) occurs.
/// Any class can call an event with an arbitrary key. However the keys should be
/// strictly entered into MediatorKeys.h where we can track all the events.
/// Note: An event is always called with a MediatorArg. The MediatorArg holds a void* to
/// an arbitrary object which the listener can cast to the correct pointer type. The listener
/// must know what kind of object to cast to.
///
/// Callback functions are of type   void func(MediatorArg);

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

#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <map>
#include <QString>
#include <vector>
#include <functional>
#include "MediatorArg.h"

//namespace drc {
//namespace drc_shared {

///
/// \brief MediatorCallbackFunc
///
/// This is the function signature of all callbacks.
/// Note: this will work with global functions, member functions and lambdas.
///
/// Global Example:
/// void GlobalFunction(MediatorArg arg);
///
/// Class Member Function Example:
/// void SomeClass::MemberFunction(MediatorArg arg);
///
/// Lambda Example:
/// [](MediatorArg arg) { /* your code here */ }

typedef std::function<void(MediatorArg mediatorArg)> MediatorCallbackFunc;				// Lambda signature

// MediatorCallback
// This is a wrapper for MediatorCallbackFunc that tracks a unique id.
// The caller can use the id to unregister the function at a later date.
typedef unsigned int MediatorId;
static MediatorId __MEDIATOR_UNIQUE_ID = 0;    // used to increment unique ids  (DON'T EDIT THIS!)
class MediatorCallback
{
public:
    MediatorCallback(MediatorCallbackFunc callback) :  _callback(callback) {_id = ++__MEDIATOR_UNIQUE_ID;}
    void Run(MediatorArg &arg) { _callback(arg); }
    inline unsigned int GetId() { return _id; }
    QString toString() { return _callback.target_type().name(); }

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
/// MediatorCallbackFunc functions are of type   std::function<void(MediatorArg mediatorArg)>

class Mediator
{
private:
	Mediator() {/*Filler!!*/ }

	Mediator(const Mediator&) {/*Filler!!*/ }

	Mediator& operator = (const Mediator&);

	~Mediator() {/*Filler!!*/ }

	static Mediator& Instance();

    typedef std::vector<MediatorCallback*> MediatorCallbackVector;
    typedef std::map<QString, MediatorCallbackVector> MediatorCallbackMap;
    MediatorCallbackMap _mediatorMap;

public:

    static MediatorId Register(QString key, MediatorCallbackFunc function);
    static MediatorId Register(QString key, MediatorCallback* callback);

    static void Unregister(QString Key, MediatorId callbackId);

	// Call Override to package arguments into a MediatorArg
	static void Call(QString key, void* object = nullptr, bool success = true, QString errorMessage = "");
	static void Call(QString Key, MediatorArg Object);

	static void Clear();

    static void PrintState();
};

//}   // end namespace drc_shared
//}   // end namespace drc

#endif

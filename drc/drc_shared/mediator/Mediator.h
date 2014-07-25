#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <map>
#include <QString>
#include <vector>
#include <functional>
#include "MediatorArg.h"

//namespace drc {
//namespace drc_shared {

/*!
 * \brief MediatorCallbackFunc
 * This is the function signature of all callbacks.
 *
 * Note: this will work with global functions, member functions and lambdas.
 * Global Example:
 * void GlobalFunction(MediatorArg arg);
 *
 * Class Member Function Example:
 * void SomeClass::MemberFunction(MediatorArg arg);
 *
 * Lambda Example:
 * [](MediatorArg arg) {  your code here  }
 *
 */
typedef std::function<void(MediatorArg mediatorArg)> MediatorCallbackFunc;	// Lambda signature

/// MediatorCallback
/// This is a wrapper for MediatorCallbackFunc that tracks a unique id.
/// The caller can use the id to unregister the function at a later date.
typedef unsigned int MediatorId;
static MediatorId __MEDIATOR_UNIQUE_ID = 0;    // used to increment unique ids  (DON'T EDIT THIS!)

/*!
 * \brief The MediatorCallback class
 *
 *  MediatorCallbackFunc functions are of type std::function<void(MediatorArg mediatorArg).
 */
class MediatorCallback
{
public:
    /*!
     * \brief MediatorCallback
     * \param callback
     */
    MediatorCallback(MediatorCallbackFunc callback) :  _callback(callback) {_id = ++__MEDIATOR_UNIQUE_ID;}
    /*!
     * \brief Run
     * \param arg
     */
    void Run(MediatorArg &arg) { _callback(arg); }
    /*!
     * \brief GetId
     * \return
     */
    inline unsigned int GetId() { return _id; }
    /*!
     * \brief toString
     * \return
     */
    QString toString() { return _callback.target_type().name(); }

private:
    MediatorId _id;
    MediatorCallbackFunc _callback;
};

/*!
 * \brief The Mediator class
 * This is the primary class for registering to listne for events and signaling events.
 * A listener will register a callback function that is fired whenever the event (key) occurs.
 * Any class can call an event with an arbitrary key. However the keys should be
 * strictly entered into MediatorKeys.h where we can track all the events.
 * Note: An event is always called with a MediatorArg. The MediatorArg holds a void* to
 * an arbitrary object which the listener can cast to the correct pointer type. The listener
 * must know what kind of object to cast to.
 *
 */
class Mediator
{
private:
	Mediator() {/*Filler!!*/ }
    /*!
     * \brief Mediator
     */
	Mediator(const Mediator&) {/*Filler!!*/ }
	Mediator& operator = (const Mediator&);
	~Mediator() {/*Filler!!*/ }

	static Mediator& Instance();

    typedef std::vector<MediatorCallback*> MediatorCallbackVector;
    typedef std::map<QString, MediatorCallbackVector> MediatorCallbackMap;
    MediatorCallbackMap _mediatorMap;

public:
    /*!
     * \brief Register
     * \param key
     * \param function
     * \return
     */
    static MediatorId Register(QString key, MediatorCallbackFunc function);
    /*!
     * \brief Register
     * \param key
     * \param callback
     * \return
     */
    static MediatorId Register(QString key, MediatorCallback* callback);
    /*!
     * \brief Unregister
     * \param Key
     * \param callbackId
     */
    static void Unregister(QString Key, MediatorId callbackId);

	// Call Override to package arguments into a MediatorArg
    /*!
     * \brief Call
     * \param key
     * \param object
     * \param success
     * \param errorMessage
     */
    static void Call(QString key, void* object = nullptr, bool success = true, QString errorMessage = "");
    /*!
     * \brief Call
     * \param Key
     * \param Object
     */
    static void Call(QString Key, MediatorArg Object);
    /*!
     * \brief Clear
     */
	static void Clear();
    /*!
     * \brief PrintState
     */
    static void PrintState();

    // Test Helpers
    /*!
     * \brief GetRegisteredCount
     * \param key
     * \return
     */
    static int GetRegisteredCount(QString key);
};

//}   // end namespace drc_shared
//}   // end namespace drc

#endif

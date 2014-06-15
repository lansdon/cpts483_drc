//
//  MediatorArg.h
//  mediator_test
//
//  Created by Lansdon Page on 5/25/14.
//  Copyright (c) 2014 lp. All rights reserved.
//

#ifndef mediator_test_MediatorArg_h
#define mediator_test_MediatorArg_h

#include <assert.h>
#include <typeinfo>
#include <type_traits>
#include <QString>
#include <iostream>

//namespace drc {
//namespace drc_shared {

///
/// \brief The MediatorArg class
///
/// This wraps a void* object used as an argument. The reciever must know what kind of * to cast to.
/// Use GetArg<PointerType*> to get the object automatically cast.  ex:  Dog* myDogPtr = GetArg<Dog*>();
/// Also includes optional meta settings:
/// bool success    (defaults to true)
/// string errorMessage (defaults to "")

class MediatorArg
{
public:
	MediatorArg(void* arg = nullptr, bool success = true, QString errorMessage = "")
	: _arg(arg)
	, _success(success)
	, _errorMessage(errorMessage)
    {}
	~MediatorArg() { }
	
	// Accessors
    bool IsSuccessful() { return _success; }
	void SetSuccessful(bool isSuccessful) { _success = isSuccessful; }
	QString ErrorMessage() { return _errorMessage; }
	void SetErrorMsg(QString errorMessage) { _errorMessage = errorMessage; }
    void SetArg(void* arg = nullptr, bool success=true, QString error = "") { _arg = arg; _success = success; _errorMessage = error;}
	
	// Cast the argument to expected type (Must be a pointer!)
	template<typename T>
	T getArg() {
		
		// Verify T is a pointer. MUST BE A POINTER
		assert(std::is_pointer<T>::value);
		
		// Special case for no arguments
		if(_arg == nullptr) return nullptr;
		
		if (T result = static_cast<T>(_arg)) {
			return result;
		} else {
			std::cerr << "Mediator arg conversion error. Cannot cast to " << typeid(T).name() << "\n";
			assert(false);
			return nullptr;
		}
    }
	
private:
	void* _arg;					// optional pointer to some object
	
	// Meta data
	bool _success;				// Success or fail status of the caller
	QString _errorMessage;	// Reason for the error
	
	// ... We can add other meta as desired
	
};

//}   // end namespace drc_shared
//}   // end namespace drc

#endif

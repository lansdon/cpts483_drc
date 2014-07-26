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

/*!
 * \brief The MediatorArg class
 * This wraps a void* object used as an argument.
 *
 * The reciever must know what kind of * to cast to
 * Use GetArg<PointerType*> to get the object automatically cast.  ex:  Dog* myDogPtr = GetArg<Dog*>();
 * Also includes optional meta settings:
 * bool success    (defaults to true)
 * string errorMessage (defaults to "").
 */
class MediatorArg
{
public:
    /*!
     * \brief MediatorArg
     * \param arg
     * \param success
     * \param errorMessage
     */
	MediatorArg(void* arg = nullptr, bool success = true, QString errorMessage = "")
	: _arg(arg)
	, _success(success)
	, _errorMessage(errorMessage)
    {}
	~MediatorArg() { }
	
	// Accessors
    /*!
     * \brief IsSuccessful
     * \return
     */
    bool IsSuccessful() { return _success; }
    /*!
     * \brief SetSuccessful
     * \param isSuccessful
     */
    void SetSuccessful(bool isSuccessful) { _success = isSuccessful; }
    /*!
     * \brief ErrorMessage
     * \return
     */
    QString ErrorMessage() { return _errorMessage; }
    /*!
     * \brief SetErrorMsg
     * \param errorMessage
     */
    void SetErrorMsg(QString errorMessage) { _errorMessage = errorMessage; }
    /*!
     * \brief SetArg
     * \param arg
     * \param success
     * \param error
     */
    void SetArg(void* arg = nullptr, bool success=true, QString error = "") { _arg = arg; _success = success; _errorMessage = error;}
	
	// Cast the argument to expected type (Must be a pointer!)
    // Example:
    // Dog* dogPtr = mediatorInstance.getArg<Dog*>();
    template<typename T>
	T getArg() {
        // Special case for no arguments
        if(_arg == nullptr) return nullptr;

		// Verify T is a pointer. MUST BE A POINTER
		assert(std::is_pointer<T>::value);
		
        try
        {
            if (T result = static_cast<T>(_arg)) {
                return result;
            } else {
                std::cerr << "\n\n************  Mediator arg conversion error. Cannot cast to " << typeid(T).name() << "\n\n";
//                assert(false);
                return nullptr;
            }
        }
        catch (std::exception ex)
        {
            std::cerr << "\n\n************  Mediator arg conversion exception.\n\n";
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

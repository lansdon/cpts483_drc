#include "mediatortests.h"
#include "AutoTest.h"
#include "Mediator.h"

const QString TEST_KEY = "TEST_KEY";

void MediatorTests::initTestCase()
{
    Mediator::Clear();
    QVERIFY(Mediator::GetRegisteredCount(TEST_KEY) == 0);
}

void MediatorTests::TestRegister1()
{
    _callbackId1 = Mediator::Register(TEST_KEY, [this](MediatorArg arg){Callback1(arg);});
    QVERIFY(Mediator::GetRegisteredCount(TEST_KEY) == 1);
}

void MediatorTests::TestRegister2()
{
    _callbackId2 = Mediator::Register(TEST_KEY, [this](MediatorArg arg){Callback2(arg);});
    QVERIFY(Mediator::GetRegisteredCount(TEST_KEY) == 2);
}

void MediatorTests::TestCall()
{
    _call1 = _call2 = false;
    Mediator::Call(TEST_KEY);
    QVERIFY(_call1);
    QVERIFY(_call2);
}

void MediatorTests::TestUnregister2()
{
    Mediator::Unregister(TEST_KEY, _callbackId2);
    QVERIFY(Mediator::GetRegisteredCount(TEST_KEY) == 1);
}

void MediatorTests::TestUnregister1()
{
    Mediator::Unregister(TEST_KEY, _callbackId1);
    QVERIFY(Mediator::GetRegisteredCount(TEST_KEY) == 0);
}

void MediatorTests::cleanupTestCase()
{
    Mediator::Clear();
}

void MediatorTests::Callback1(MediatorArg arg)
{
    Q_UNUSED(arg);
    _call1 = true;
}

void MediatorTests::Callback2(MediatorArg arg)
{
    Q_UNUSED(arg);
    _call2 = true;
}

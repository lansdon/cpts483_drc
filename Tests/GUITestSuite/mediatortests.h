#ifndef MEDIATORTESTS_H
#define MEDIATORTESTS_H

#include "AutoTest.h"
#include "Mediator.h"

class MediatorTests : public QObject
{
    Q_OBJECT
private:
    MediatorId _callbackId1; // use to register/unregister
    MediatorId _callbackId2; // use to register/unregister
    bool _call1, _call2;
    void Callback1(MediatorArg arg);
    void Callback2(MediatorArg arg);

private slots:
    void initTestCase();
    void TestRegister1();
    void TestRegister2();
    void TestCall();
    void TestUnregister2();
    void TestUnregister1();
    void cleanupTestCase();
};

DECLARE_TEST(MediatorTests)

#endif // MEDIATORTESTS_H

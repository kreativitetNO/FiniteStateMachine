#ifndef MYFUNCTIONALCLASS_H
#define MYFUNCTIONALCLASS_H

#include "GlobalData.h"
#include "Fsm/FiniteStateMachine.h"
#include "StateBase.h"
#include "State1.h"
#include "State2.h"

class MyFunctionalClass
    : public MyFunctionalClassFsm
{
    public:
    MyFunctionalClass(ISomeInterface& someDependency)
        : MyFunctionalClassFsm { globalData_ }
    {
        registerState<State1>();
        registerState<State2>(someDependency);
    }

    void startStateMachine()
    {
        changeState<State1>();
    }

    void stateMethod()
    {
        currentState().stateMethod();
    }

    void stateSwappingMethod()
    {
        currentState().stateSwappingMethod();
    }

    private:
    GlobalData globalData_;
};


#endif
#ifndef STATEBASE_H
#define STATEBASE_H

#include "GlobalData.h"
#include "Fsm/FiniteStateMachine.h"

class StateBase;
using MyFunctionalClassFsm = typename Fsm::FiniteStateMachine<StateBase,GlobalData>;

class StateBase : public MyFunctionalClassFsm::StateBase
{
    public:

    StateBase(MyFunctionalClassFsm& finiteStateMachine,
              GlobalData& sharedData)
        : MyFunctionalClassFsm::StateBase { finiteStateMachine, sharedData }
    {}
    
    virtual void stateSwappingMethod() {}
    virtual void stateMethod() {}
};

#endif
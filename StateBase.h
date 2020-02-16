#ifndef STATEBASE_H
#define STATEBASE_H

#include "GlobalData.h"
#include "Fsm/StateBase.h"
#include "Fsm/FiniteStateMachine.h"

class StateBase : public Fsm::StateBase<Fsm::FiniteStateMachine<StateBase,GlobalData>,GlobalData>
{
    public:

    StateBase(Fsm::FiniteStateMachine<StateBase,GlobalData>& finiteStateMachine,
              GlobalData& sharedData)
        : Fsm::StateBase<Fsm::FiniteStateMachine<StateBase,GlobalData>,GlobalData> { finiteStateMachine, sharedData }
    {}
    
    virtual void stateSwappingMethod() {}
    virtual void stateMethod() {}
};

#endif
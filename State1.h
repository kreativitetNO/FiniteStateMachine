#ifndef STATE1_H
#define STATE1_H

#include <iostream>
#include "StateBase.h"

class State2;

class State1 : public StateBase
{
    public:
    State1(Fsm::FiniteStateMachine<StateBase,GlobalData>& finiteStateMachine,
           GlobalData& globalData)
        : StateBase { finiteStateMachine, globalData }
    {}

    void onEntry() override
    {
        std::cout << "Entered State1" << std::endl;
    }

    void onExit() override
    {
        std::cout << "Exitted State1" << std::endl;
    }

    void stateSwappingMethod() override
    {
        finiteStateMachine_.changeState<State2>();
    }

    void stateMethod() override
    {
        sharedData_.globalDataVariable_ -= 1;
        std::cout << "State 1 - someMethod()  - globalData_.globalDataVariable_ = "
                  << sharedData_.globalDataVariable_ << std::endl;
    }
};


#endif
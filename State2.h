#ifndef STATE2_H
#define STATE2_H

#include <iostream>
#include "ISomeInterface.h"
#include "StateBase.h"

class State2 : public StateBase
{
    public:
    State2(MyFunctionalClassFsm& finiteStateMachine,
           GlobalData& globalData,
           ISomeInterface& someDependency)
        : StateBase { finiteStateMachine, globalData }
        , someDependency_ { someDependency }
    {}

    void onEntry() override
    {
        std::cout << "Entered State2" << std::endl;
    }

    void onExit() override
    {
        std::cout << "Exitted State2" << std::endl;
    }

    void stateSwappingMethod() override
    {
        finiteStateMachine_.changeState<State1>();
    }

    void stateMethod() override
    {
        sharedData_.globalDataVariable_ += 1;
        std::cout << "State 2 - someMethod() - globalData_.globalDataVariable_ = "
                  << sharedData_.globalDataVariable_ << std::endl;
        someDependency_.someInterfaceMethod();
    }

    private:
    ISomeInterface& someDependency_;
};

#endif
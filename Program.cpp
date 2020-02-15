#include <iostream>

#include "Fsm/Data.h"
#include "Fsm/StateBase.h"
#include "Fsm/FiniteStateMachine.h"

class State2;

class State1 : public StateBase
{
    public:
    State1(FiniteStateMachine& finiteStateMachine,
           GlobalData& globalData,
           StateData& stateData)
        : StateBase { finiteStateMachine, globalData, stateData }
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
        std::cout << "State 1 - someMethod()" << std::endl;
    }
};

class State2 : public StateBase
{
    public:
    State2(FiniteStateMachine& finiteStateMachine,
           GlobalData& globalData,
           StateData& stateData,
           int someDependency)
        : StateBase { finiteStateMachine, globalData, stateData }
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
        std::cout << "State 2 - someMethod()" << std::endl;
    }
};

class MyFunctionalClass
    : public FiniteStateMachine
{
    public:
    MyFunctionalClass()
    {
        registerState<State1>();
        registerState<State2>(4);
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
};

int main()
{
    /* Matt Parker - How to program math programs video */

    MyFunctionalClass mfc;

    mfc.changeState<State1>();

    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
}
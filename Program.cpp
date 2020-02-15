#include <iostream>

#include "Fsm/StateBaseTemplate.h"
#include "Fsm/FiniteStateMachine.h"

struct SharedData
{
    double globalDataVariable_ = 5.0;
};

class StateBase : public StateBaseTemplate<FiniteStateMachine<StateBase,SharedData>, SharedData>
{
    public:
    StateBase(FiniteStateMachine<StateBase,SharedData>& finiteStateMachine,
              SharedData& sharedData)
        : StateBaseTemplate<FiniteStateMachine<StateBase,SharedData>, SharedData> { finiteStateMachine, sharedData }
    {}
    virtual void stateSwappingMethod() {}
    virtual void stateMethod() {}
};

class State2;

class State1 : public StateBase
{
    public:
    State1(FiniteStateMachine<StateBase,SharedData>& finiteStateMachine,
           SharedData& globalData)
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

class State2 : public StateBase
{
    public:
    State2(FiniteStateMachine<StateBase,SharedData>& finiteStateMachine,
           SharedData& globalData,
           int someDependency)
        : StateBase { finiteStateMachine, globalData }
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
    }
};

class MyFunctionalClass
    : public FiniteStateMachine<StateBase,SharedData>
{
    public:
    MyFunctionalClass()
        : FiniteStateMachine<StateBase,SharedData> { globalData_ }
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
    SharedData globalData_;
};

int main()
{
    MyFunctionalClass mfc;

    mfc.changeState<State1>();

    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
}
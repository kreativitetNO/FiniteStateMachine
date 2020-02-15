#ifndef STATEBASE_H
#define STATEBASE_H

#include "Data.h"

class FiniteStateMachine;

class StateBase
{
    public:
    StateBase() = default;
    StateBase(FiniteStateMachine& finiteStateMachine,
              GlobalData& globalData,
              StateData& stateData)
        : finiteStateMachine_ { finiteStateMachine }
        , globalData_ { globalData }
        , stateData_ { stateData }
    {}
    StateBase(StateBase const&) = delete;
    StateBase& operator=(StateBase const&) = delete;
    StateBase(StateBase&&) = delete;
    StateBase& operator=(StateBase&&) = delete;
    virtual ~StateBase() = default;

    virtual void onEntry() {}
    virtual void onExit() {}
    virtual void stateSwappingMethod() {}
    virtual void stateMethod() {}

    protected:
    FiniteStateMachine& finiteStateMachine_;
    GlobalData& globalData_;
    StateData& stateData_;
};

#endif
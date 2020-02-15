#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <cstdlib>
#include <memory>
#include <map>
#include <typeinfo>
#include <utility>

#include "Data.h"
#include "StateBase.h"

template <typename GlobalData, typename StateData>
class FiniteStateMachine
{
    public:
    FiniteStateMachine() = default;
    FiniteStateMachine(FiniteStateMachine const&) = delete;
    FiniteStateMachine& operator=(FiniteStateMachine const&) = delete;
    FiniteStateMachine(FiniteStateMachine&&) = delete;
    FiniteStateMachine& operator=(FiniteStateMachine&&) = delete;

    class StateBase;

    StateBase& currentState();
    template <typename StateType>
    void changeState();

    protected:
    template <typename StateType>
    void registerState();
    template <typename StateType, typename...CtorArgs>
    void registerState(CtorArgs...ctorArgs);
    using StateMap = std::map<size_t, std::unique_ptr<StateBase>>;
    StateMap states_;
    size_t currentStateHash_;
    GlobalData globalData_;
    StateData stateData_;
};

template <typename GlobalData, typename StateData>
class FiniteStateMachine<GlobalData, StateData>::StateBase
{
    public:
    StateBase() = default;
    StateBase(FiniteStateMachine& finiteStateMachine,
                GlobalData& globalData,
                StateData& stateData);
    StateBase(StateBase const&) = delete;
    StateBase& operator=(StateBase const&) = delete;
    StateBase(StateBase&&) = delete;
    StateBase& operator=(StateBase&&) = delete;
    virtual ~StateBase() = default;

    virtual void onEntry() {}
    virtual void onExit() {}

    protected:
    FiniteStateMachine& finiteStateMachine_;
    GlobalData& globalData_;
    StateData& stateData_;
};

template <typename GlobalData, typename StateData>
FiniteStateMachine<GlobalData, StateData>::StateBase& FiniteStateMachine<GlobalData, StateData>::currentState()
{
    auto currentStatePair = states_.find(currentStateHash_);
    if (currentStatePair == states_.end())
    {
        throw std::exception{};
    }
    return *(currentStatePair->second.get());
}

template <typename GlobalData, typename StateData>
template <typename StateType>
void FiniteStateMachine<GlobalData, StateData>::changeState()
{
    auto currentState = states_.find(currentStateHash_);
    if (currentState != states_.end() && currentState->second)
    {
        currentState->second->onExit();            
    }
    auto newType = states_.find((typeid(StateType)).hash_code());
    if (newType == states_.end())
    {
        throw std::exception {};
    }
    currentStateHash_ = newType->first;
    if (newType->second)
    {
        newType->second->onEntry();
    }
}

template <typename GlobalData, typename StateData>
template <typename StateType>
void FiniteStateMachine<GlobalData, StateData>::registerState()
{
    states_[typeid(StateType).hash_code()] = std::make_unique<StateType>(*this, globalData_, stateData_);
}

template <typename GlobalData, typename StateData>
template <typename StateType, typename...CtorArgs>
void FiniteStateMachine<GlobalData, StateData>::registerState(CtorArgs...ctorArgs)
{
    states_[typeid(StateType).hash_code()] =
        std::make_unique<StateType>(*this, globalData_, stateData_, std::forward<CtorArgs>(ctorArgs)... );
}

template <typename GlobalData, typename StateData>
FiniteStateMachine<GlobalData, StateData>::StateBase::StateBase(FiniteStateMachine& finiteStateMachine,
                                                                GlobalData& globalData,
                                                                StateData& stateData)
    : finiteStateMachine_ { finiteStateMachine }
    , globalData_ { globalData }
    , stateData_ { stateData }
{}

#endif
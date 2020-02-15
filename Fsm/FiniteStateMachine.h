#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <cstdlib>
#include <memory>
#include <map>
#include <typeinfo>
#include <utility>

#include "Data.h"
#include "StateBase.h"

class FiniteStateMachine
{
    public:
    FiniteStateMachine() = default;
    FiniteStateMachine(FiniteStateMachine const&) = delete;
    FiniteStateMachine& operator=(FiniteStateMachine const&) = delete;
    FiniteStateMachine(FiniteStateMachine&&) = delete;
    FiniteStateMachine& operator=(FiniteStateMachine&&) = delete;

    StateBase& currentState()
    {
        auto currentStatePair = states_.find(currentStateHash_);
        if (currentStatePair == states_.end())
        {
            throw std::exception{};
        }
        return *(currentStatePair->second.get());
    }

    template <typename StateType>
    void changeState()
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

    protected:
    template <typename StateType>
    void registerState()
    {
        states_[typeid(StateType).hash_code()] = std::make_unique<StateType>(*this, globalData_, stateData_);
    }
    template <typename StateType, typename...CtorArgs>
    void registerState(CtorArgs...ctorArgs)
    {
        states_[typeid(StateType).hash_code()] = std::make_unique<StateType>(*this, globalData_, stateData_, std::forward<CtorArgs>(ctorArgs)... );
    }
    using StateMap = std::map<size_t, std::unique_ptr<StateBase>>;
    StateMap states_;
    size_t currentStateHash_;
    GlobalData globalData_;
    StateData stateData_;
};

#endif
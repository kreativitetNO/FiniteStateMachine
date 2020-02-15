#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <cstdlib>
#include <memory>
#include <map>
#include <typeinfo>
#include <utility>

template <typename StateBase, typename SharedData>
class FiniteStateMachine
{
    public:
    FiniteStateMachine(SharedData& sharedData);
    FiniteStateMachine(FiniteStateMachine const&) = delete;
    FiniteStateMachine& operator=(FiniteStateMachine const&) = delete;
    FiniteStateMachine(FiniteStateMachine&&) = delete;
    FiniteStateMachine& operator=(FiniteStateMachine&&) = delete;

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
    SharedData& sharedData_;
};

template <typename StateBase, typename SharedData>
FiniteStateMachine<StateBase, SharedData>::FiniteStateMachine(SharedData& sharedData)
    : sharedData_ { sharedData }
{
}

template <typename StateBase, typename SharedData>
StateBase& FiniteStateMachine<StateBase, SharedData>::currentState()
{
    auto currentStatePair = states_.find(currentStateHash_);
    if (currentStatePair == states_.end())
    {
        throw std::exception{};
    }
    return *(currentStatePair->second.get());
}

template <typename StateBase, typename SharedData>
template <typename StateType>
void FiniteStateMachine<StateBase, SharedData>::changeState()
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

template <typename StateBase, typename SharedData>
template <typename StateType>
void FiniteStateMachine<StateBase, SharedData>::registerState()
{
    states_[typeid(StateType).hash_code()] = std::make_unique<StateType>(*this, sharedData_);
}

template <typename StateBase, typename SharedData>
template <typename StateType, typename...CtorArgs>
void FiniteStateMachine<StateBase, SharedData>::registerState(CtorArgs...ctorArgs)
{
    states_[typeid(StateType).hash_code()] =
        std::make_unique<StateType>(*this, sharedData_, std::forward<CtorArgs>(ctorArgs)... );
}

#endif
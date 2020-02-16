#ifndef FSM_FINITESTATEMACHINE_H
#define FSM_FINITESTATEMACHINE_H

#include <cstdlib>
#include <memory>
#include <map>
#include <typeinfo>
#include <utility>

namespace Fsm
{
    template <typename FsmStateBase, typename SharedDataType>
    class FiniteStateMachine
    {
        public:
        class StateBase;

        FiniteStateMachine(SharedDataType& sharedData);
        FiniteStateMachine(FiniteStateMachine const&) = delete;
        FiniteStateMachine& operator=(FiniteStateMachine const&) = delete;
        FiniteStateMachine(FiniteStateMachine&&) = delete;
        FiniteStateMachine& operator=(FiniteStateMachine&&) = delete;

        auto& currentState();
        template <typename StateType>
        void changeState();

        protected:
        template <typename StateType>
        void registerState();
        template <typename StateType, typename...CtorArgs>
        void registerState(CtorArgs&&...ctorArgs);
        using StateMap = std::map<size_t, std::unique_ptr<FsmStateBase>>;
        StateMap states_;
        size_t currentStateHash_;
        SharedDataType& sharedData_;
    };

    template <typename FsmStateBase, typename SharedDataType>
    class FiniteStateMachine<FsmStateBase,SharedDataType>::StateBase
    {
        public:
        StateBase() = default;
        StateBase(FiniteStateMachine& finiteStateMachine,
                  SharedDataType& sharedData);
        StateBase(StateBase const&) = delete;
        StateBase& operator=(StateBase const&) = delete;
        StateBase(StateBase&&) = delete;
        StateBase& operator=(StateBase&&) = delete;
        virtual ~StateBase() = default;

        virtual void onEntry() {}
        virtual void onExit() {}

        protected:
        SharedDataType& sharedData_;
        FiniteStateMachine& finiteStateMachine_;
    };
}

template <typename FsmStateBase, typename SharedDataType>
Fsm::FiniteStateMachine<FsmStateBase,SharedDataType>::FiniteStateMachine(SharedDataType& sharedData)
    : sharedData_ { sharedData }
{
}

template <typename FsmStateBase, typename SharedDataType>
auto&
Fsm::FiniteStateMachine<FsmStateBase,SharedDataType>::currentState()
{
    auto currentStatePair = states_.find(currentStateHash_);
    if (currentStatePair == states_.end())
    {
        throw std::exception{};
    }
    return *(currentStatePair->second.get());
}

template <typename FsmStateBase,typename SharedDataType>
template <typename StateType>
void
Fsm::FiniteStateMachine<FsmStateBase,SharedDataType>::changeState()
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

template <typename FsmStateBase, typename SharedData>
template <typename StateType>
void
Fsm::FiniteStateMachine<FsmStateBase,SharedData>::registerState()
{
    states_[typeid(StateType).hash_code()] = std::make_unique<StateType>(*this, sharedData_);
}

template <typename FsmStateBase, typename SharedDataType>
template <typename StateType, typename...CtorArgs>
void
Fsm::FiniteStateMachine<FsmStateBase,SharedDataType>::registerState(CtorArgs&&...ctorArgs)
{
    states_[typeid(StateType).hash_code()] =
        std::make_unique<StateType>(*this, sharedData_, std::forward<CtorArgs>(ctorArgs)... );
}

template <typename FsmStateBase, typename SharedDataType>
Fsm::FiniteStateMachine<FsmStateBase,SharedDataType>::StateBase::StateBase(FiniteStateMachine& finiteStateMachine,
                                                                           SharedDataType& sharedData)
    : finiteStateMachine_ { finiteStateMachine }
    , sharedData_ { sharedData }
{}

#endif
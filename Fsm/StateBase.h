#ifndef FSM_STATEBASE_H
#define FSM_STATEBASE_H

namespace Fsm
{
    template <typename FiniteStateMachine, typename SharedData>
    class StateBase
    {
        public:
        StateBase() = default;
        StateBase(FiniteStateMachine& finiteStateMachine,
                  SharedData& sharedData);
        StateBase(StateBase const&) = delete;
        StateBase& operator=(StateBase const&) = delete;
        StateBase(StateBase&&) = delete;
        StateBase& operator=(StateBase&&) = delete;
        virtual ~StateBase() = default;

        virtual void onEntry() {}
        virtual void onExit() {}

        SharedData& sharedData_;

        protected:
        FiniteStateMachine& finiteStateMachine_;
    };
}

template <typename FiniteStateMachine, typename SharedData>
Fsm::StateBase<FiniteStateMachine,SharedData>::StateBase(FiniteStateMachine& finiteStateMachine,
                                                         SharedData& sharedData)
    : finiteStateMachine_ { finiteStateMachine }
    , sharedData_ { sharedData }
{}

#endif
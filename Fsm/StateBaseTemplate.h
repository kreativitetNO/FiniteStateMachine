#ifndef STATEBASETEMPLATE_H
#define STATEBASETEMPLATE_H

template <typename FiniteStateMachine, typename SharedData>
class StateBaseTemplate
{
    public:
    StateBaseTemplate() = default;
    StateBaseTemplate(FiniteStateMachine& finiteStateMachine,
                      SharedData& sharedData);
    StateBaseTemplate(StateBaseTemplate const&) = delete;
    StateBaseTemplate& operator=(StateBaseTemplate const&) = delete;
    StateBaseTemplate(StateBaseTemplate&&) = delete;
    StateBaseTemplate& operator=(StateBaseTemplate&&) = delete;
    virtual ~StateBaseTemplate() = default;

    virtual void onEntry() {}
    virtual void onExit() {}

    SharedData& sharedData_;

    protected:
    FiniteStateMachine& finiteStateMachine_;
};

template <typename FiniteStateMachine, typename SharedData>
StateBaseTemplate<FiniteStateMachine,SharedData>::StateBaseTemplate(FiniteStateMachine& finiteStateMachine,
                                                                    SharedData& sharedData)
    : finiteStateMachine_ { finiteStateMachine }
    , sharedData_ { sharedData }
{}

#endif
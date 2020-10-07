#pragma once

#include "Transition.h"

template<typename ATT>
class State
{
public:
    explicit State() = default;
    virtual ~State() = default;

    void SetStateMachine(ATT* stateMachine);
    virtual void UpdateState() = 0;

protected:
    ATT* mAttribute;

};

template <typename ATT>
void State<ATT>::SetStateMachine(ATT* stateMachine)
{
    mAttribute = stateMachine;
}

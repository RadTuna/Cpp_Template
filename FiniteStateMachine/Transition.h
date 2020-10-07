#pragma once

#include <string>

template<typename ATT>
class Transition
{
public:
    explicit Transition() = default;
    virtual ~Transition() = default;

    void SetStateMachine(ATT* stateMachine);
    virtual bool IsTransition() = 0;

protected:
    ATT* mAttribute;

};

template <typename ATT>
void Transition<ATT>::SetStateMachine(ATT* stateMachine)
{
    mAttribute = stateMachine;
}

#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "State.h"
#include "Transition.h"

template<typename ATT>
class StateMachine
{
public:
    explicit StateMachine() = default;
    explicit StateMachine(std::unique_ptr<State<ATT>>&& entryState);
    virtual ~StateMachine() = default;

    bool SetEntryState(const State<ATT>* state);
    const State<ATT>* AddState(std::unique_ptr<State<ATT>>&& state);
    bool RemoveState(const State<ATT>* state);

    const Transition<ATT>* AddTransition(std::unique_ptr<Transition<ATT>>&& transition, const State<ATT>* srcState, const State<ATT>* destState);
    bool RemoveTransition(const Transition<ATT>* transition);

    ATT& GetAttribute();

    void UpdateStateMachine();

private:
    bool IsValidState(const State<ATT>* state) const;
    bool IsValidTransition(const Transition<ATT>* transition) const;

private:
    std::vector<std::unique_ptr<State<ATT>>> mStates;
    std::vector<std::unique_ptr<Transition<ATT>>> mTransitions;

    std::unordered_map<const State<ATT>*, std::vector<Transition<ATT>*>> mSrcTransitionMap;
    std::unordered_map<Transition<ATT>*, State<ATT>*> mDestTransitionMap;

    State<ATT>* mActiveState;

    ATT mAttribute;

};

template<typename ATT>
StateMachine<ATT>::StateMachine(std::unique_ptr<State<ATT>>&& entryState)
{
    AddState(std::move(entryState));
    mActiveState = entryState.get();
}

template<typename ATT>
bool StateMachine<ATT>::SetEntryState(const State<ATT>* state)
{
    assert(state != nullptr);

    const auto findIter = std::find_if(mStates.begin(), mStates.end(), 
        [state](const std::unique_ptr<State<ATT>>& element) -> bool
        {
            return element.get() == state;
        });

    if (findIter == mStates.end())
    {
        return false;
    }

    mActiveState = findIter->get();
    return true;
}

template<typename ATT>
const State<ATT>* StateMachine<ATT>::AddState(std::unique_ptr<State<ATT>>&& state)
{
    State<ATT>* statePtr = state.get();
    state->SetStateMachine(&mAttribute);
    mStates.emplace_back(std::move(state));
    return statePtr;
}

template<typename ATT>
bool StateMachine<ATT>::RemoveState(const State<ATT>* state)
{
    assert(state != nullptr);

    const auto findIter = std::find_if(mStates.begin(), mStates.end(), 
        [state](const std::unique_ptr<State<ATT>>& element) -> bool
        {
            return element.get() == state;
        });

    if (findIter == mStates.end())
    {
        return false;
    }

    mStates.erase(findIter);

    mSrcTransitionMap.erase(state);

    const auto findDestIter = std::find_if(mDestTransitionMap.begin(), mDestTransitionMap.end(),
        [state](std::pair<Transition<ATT>*, State<ATT>*>& element) -> bool
        {
            return element.second == state;  
        });
    mDestTransitionMap.erase(findDestIter);

    return true;
}

template<typename ATT>
const Transition<ATT>* StateMachine<ATT>::AddTransition(std::unique_ptr<Transition<ATT>>&& transition, const State<ATT>* srcState, const State<ATT>* destState)
{
    assert(srcState != nullptr);
    assert(destState != nullptr);

    if (!IsValidState(srcState))
    {
        return nullptr;
    }

    if (!IsValidState(destState))
    {
        return nullptr;
    }

    Transition<ATT>* transitionPtr = transition.get();
    transition->SetStateMachine(&mAttribute);
    mTransitions.emplace_back(std::move(transition));

    mSrcTransitionMap[srcState].emplace_back(transitionPtr);
    mDestTransitionMap[transitionPtr] = const_cast<State<ATT>*>(destState);

    return transitionPtr;
}

template<typename ATT>
bool StateMachine<ATT>::RemoveTransition(const Transition<ATT>* transition)
{
    assert(transition != nullptr);

    const auto findIter = std::find_if(mTransitions.begin(), mTransitions.end(), 
        [transition](const std::unique_ptr<Transition<ATT>>& element) -> bool
        {
            return element.get() == transition;
        });

    if (findIter == mTransitions.end())
    {
        return false;
    }

    mTransitions.erase(findIter);

    const auto findSrcIter = std::find_if(mSrcTransitionMap.begin(), mSrcTransitionMap.end(),
        [transition](std::pair<State<ATT>*, std::vector<Transition<ATT>*>>& element) -> bool
        {
            const auto findIter = std::find(element.second.begin(), element.second.end(), transition);
            if (findIter != element.second.end())
            {
                return element.second.erase(findIter);
            }
            return false;
        });
    assert(findSrcIter != mSrcTransitionMap.end());

    mSrcTransitionMap.erase(findSrcIter);
    mDestTransitionMap.erase(transition);

    return true;
}

template <typename ATT>
ATT& StateMachine<ATT>::GetAttribute()
{
    return mAttribute;
}

template <typename ATT>
void StateMachine<ATT>::UpdateStateMachine()
{
    assert(mActiveState != nullptr);

    for (Transition<ATT>* transition : mSrcTransitionMap[mActiveState])
    {
        if (transition->IsTransition())
        {
            mActiveState = mDestTransitionMap[transition];
            break;
        }
    }

    mActiveState->UpdateState();
}

template<typename ATT>
bool StateMachine<ATT>::IsValidState(const State<ATT>* state) const
{
    if (state == nullptr)
    {
        return false;
    }

    const auto findIter = std::find_if(mStates.begin(), mStates.end(), 
        [state](const std::unique_ptr<State<ATT>>& element) -> bool
        {
            return element.get() == state;
        });

    if (findIter == mStates.end())
    {
        return false;
    }

    return true;
}

template<typename ATT>
bool StateMachine<ATT>::IsValidTransition(const Transition<ATT>* transition) const
{
    if (transition == nullptr)
    {
        return false;
    }

    const auto findIter = std::find_if(mTransitions.begin(), mTransitions.end(),
        [transition](std::unique_ptr<Transition<ATT>>& element) -> bool
        {
            return element.get() == transition;
        });

    if (findIter == mTransitions.end())
    {
        return false;
    }

    return true;
}


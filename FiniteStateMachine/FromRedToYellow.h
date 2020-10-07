#pragma once

#include "Transition.h"
#include "TrafficLight.h"

class FromRedToYellow final : public Transition<TrafficLight>
{
public:
    FromRedToYellow() = default;
    ~FromRedToYellow() override = default;

    bool IsTransition() override
    {
        return mAttribute->GetTransitional();
    }
};

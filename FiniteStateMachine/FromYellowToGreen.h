#pragma once

#include "Transition.h"
#include "TrafficLight.h"

class FromYellowToGreen final : public Transition<TrafficLight>
{
public:
    FromYellowToGreen() = default;
    ~FromYellowToGreen() override = default;

    bool IsTransition() override
    {
        return mAttribute->GetTransitional();
    }
};

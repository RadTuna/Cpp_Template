#pragma once

#include "Transition.h"
#include "TrafficLight.h"

class FromGreenToRed final : public Transition<TrafficLight>
{
public:
    FromGreenToRed() = default;
    ~FromGreenToRed() override = default;

    bool IsTransition() override
    {
        return mAttribute->GetTransitional();
    }
};
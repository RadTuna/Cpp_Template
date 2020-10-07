#pragma once

#include <iostream>

#include "State.h"
#include "TrafficLight.h"

class YellowState final : public State<TrafficLight>
{
public:
    YellowState() = default;
    ~YellowState() override = default;

    void UpdateState() override
    {
        std::cout << "On Yellow Light!" << std::endl;
    }

};

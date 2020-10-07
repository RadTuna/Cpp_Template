#pragma once

#include <iostream>

#include "State.h"
#include "TrafficLight.h"

class GreenState final : public State<TrafficLight>
{
public:
    GreenState() = default;
    ~GreenState() override = default;

    void UpdateState() override
    {
        std::cout << "On Green Light!" << std::endl;
    }

};

#pragma once

#include <iostream>

#include "State.h"
#include "TrafficLight.h"

class RedState final : public State<TrafficLight>
{
public:
    RedState() = default;
    ~RedState() override = default;

    void UpdateState() override
    {
        std::cout << "On Red Light!" << std::endl;
    }

};

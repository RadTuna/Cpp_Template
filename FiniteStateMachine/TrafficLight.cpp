
#include "TrafficLight.h"

bool TrafficLight::GetTransitional() const
{
    return mIsTransitional;
}

void TrafficLight::SetTransitional(bool newValue)
{
    mIsTransitional = newValue;
}

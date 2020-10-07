#pragma once

class TrafficLight final
{
public:
    TrafficLight() = default;
    ~TrafficLight() = default;

    bool GetTransitional() const;
    void SetTransitional(bool newValue);

private:
    bool mIsTransitional;

};

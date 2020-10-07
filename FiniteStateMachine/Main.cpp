
#include <iostream>
#include <cassert>

#include "StateMachine.h"
#include "TrafficLight.h"
#include "RedState.h"
#include "YellowState.h"
#include "GreenState.h"
#include "FromRedToYellow.h"
#include "FromYellowToGreen.h"
#include "FromGreenToRed.h"

int main()
{
    StateMachine<TrafficLight> stateMachine;

    const State<TrafficLight>* redState = stateMachine.AddState(std::make_unique<RedState>());
    const State<TrafficLight>* yellowState = stateMachine.AddState(std::make_unique<YellowState>());
    const State<TrafficLight>* greenState = stateMachine.AddState(std::make_unique<GreenState>());

    stateMachine.AddTransition(std::make_unique<FromRedToYellow>(), redState, yellowState);
    stateMachine.AddTransition(std::make_unique<FromYellowToGreen>(), yellowState, greenState);
    stateMachine.AddTransition(std::make_unique<FromGreenToRed>(), greenState, redState);

    stateMachine.SetEntryState(redState);

    stateMachine.GetAttribute().SetTransitional(false);

    stateMachine.UpdateStateMachine();

    stateMachine.GetAttribute().SetTransitional(true);

    stateMachine.UpdateStateMachine();
    stateMachine.UpdateStateMachine();
    stateMachine.UpdateStateMachine();

    stateMachine.GetAttribute().SetTransitional(false);

    stateMachine.UpdateStateMachine();
    stateMachine.UpdateStateMachine();

    return 0;
}

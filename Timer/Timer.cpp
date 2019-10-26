#include "Timer.h"

Timer::Timer()
	: TimerInterval(0),
	bIsTimerEnd(false)
{
}

void Timer::ClearTimer()
{
	bIsTimerEnd = true;
}

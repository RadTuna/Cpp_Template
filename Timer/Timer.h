#pragma once

#include <thread>
#include <chrono>


class Timer
{
public:

	explicit Timer();
	Timer(const Timer& other) = delete;
	~Timer() = default;

	template<typename Fn, typename... Args>
	void SetTimer(int TimerInterval, Fn InFunc, Args... InFuncArgs);

	void ClearTimer();

private:

	template<typename Fn, typename... Args>
	void LoopTimer(Timer* pThis, Fn InFunc, Args... InFuncArgs);

private:

	int TimerInterval;
	bool bIsTimerEnd;

};

template<typename Fn, typename... Args>
void Timer::SetTimer(int InTimerInterval, Fn InFunc, Args... InFuncArgs)
{
	bIsTimerEnd = false;
	TimerInterval = InTimerInterval;

	std::thread TimerThread(&Timer::LoopTimer, this, InFunc, InFuncArgs...);
}

template<typename Fn, typename... Args>
void Timer::LoopTimer(Timer* pThis, Fn InFunc, Args... InFuncArgs)
{
	while (pThis->bIsTimerEnd == false)
	{
		InFunc(InFuncArgs...);
		std::this_thread::sleep_for(std::chrono::milliseconds(pThis->TimerInterval));
	}
}

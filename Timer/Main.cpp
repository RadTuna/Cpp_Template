#include <iostream>
#include "Timer.h"
#include <thread>

void TestFunc(int Num, float Num2)
{
	std::cout << Num << " : Execute TestFunc" << Num2 << std::endl;
}

int main()
{
	Timer MyTimer;

	MyTimer.SetTimer(500, TestFunc, 10, 1.5f);

	// 검사용 출력
	std::cout << "Main : Complete ThreadCreate" << std::endl;

	int Count = 0;
	while (Count < 1000000000)
	{
		Count++;
	}

	// 검사용 출력
	std::cout << "Main : LoopEnd!" << std::endl;

	MyTimer.ClearTimer();

	while (true) {}

	return 0;

}

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

	MyTimer.SetTimer(1000, TestFunc, 10, 1.5f);

	while(true) {}

	MyTimer.ClearTimer();

	return 0;

}

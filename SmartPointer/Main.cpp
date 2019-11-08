#include <iostream>
#include <string.h>
#include "UniquePointer.h"

struct Point
{
	float X;
	float Y;

	Point() : X(0.0f), Y(0.0f) {}
	Point(float InX, float InY) : X(InX), Y(InY) {}
};

void PrintPoint(std::string Prefix, float X, float Y)
{
	std::cout << Prefix << " / X : " << X << ", Y : " << Y << std::endl;
}

int main()
{
	UniquePointer<Point> Test = MakeUniquePointer<Point>(10.0f, 20.0f);
	UniquePointer<Point> Test2 = MakeUniquePointer<Point>(20.0f, 30.0f);

	PrintPoint("Test", Test->X, Test->Y);
	PrintPoint("Test2", Test2->X, Test2->Y);

	// Test = Test2; // Do not compiled
	
	Test = std::move(Test2);

	PrintPoint("Test", Test->X, Test->Y);
	// PrintPoint("Test2", Test2->X, Test2->Y); // Memory access error

	return 0;
}
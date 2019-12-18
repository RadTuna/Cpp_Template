
#include <iostream>

#include "CalculrateParabola.h"

int main()
{
	Parabola TestParabola;
	Vector2 Origin2D = { 0.0f, 0.0f };

	TestParabola.CalculateParabola2D(Origin2D, 45.0f, 100.0f, 0.1f);

	for (auto Location : TestParabola.GetResult2D())
	{
		std::cout << "X : " << Location.x << " / Y : " << Location.y << std::endl;
	}

	return 0;
}
#include "CalculrateParabola.h"

#define M_PI 3.14159265358979323846
#define EARTH_GRAVITY 9.8f

#include <cmath>

void Parabola::CalculateParabola2D(const Vector2& Origin, float Degree, float StartVelocity, float TickInterval)
{
	if (Degree > 180.0f || Degree < 0.0f)
	{
		return;
	}

	Vector2 PrevLocation = Origin;
	Vector2 CurrentLocation = Origin;
	float CurrentVelocity = StartVelocity;
	float CurrentRadian = Deg2Rad(Degree);

	for (; CurrentLocation.y >= 0.0f;)
	{
		PrevLocation = CurrentLocation;

		CurrentLocation.x += CurrentVelocity * std::cos(CurrentRadian) * TickInterval;
		CurrentLocation.y += (CurrentVelocity * std::sin(CurrentRadian) * TickInterval) - (0.5f * EARTH_GRAVITY * TickInterval * TickInterval);

		Vector2 Direction;
		Direction.x = CurrentLocation.x - PrevLocation.x;
		Direction.y = CurrentLocation.y - PrevLocation.y;

		float InvInterval = 1.0f / TickInterval;
		CurrentVelocity = std::sqrtf(Direction.x * Direction.x * InvInterval * InvInterval + Direction.y * Direction.y * InvInterval * InvInterval);
		CurrentRadian = std::atan2(Direction.y, Direction.x);

		Result2D.emplace_back(CurrentLocation);
	}
}

void Parabola::CalculateParabola3D(const Vector3& Origin, const Vector3& Degree, float StartVelocity, float TickInterval)
{
}

const std::vector<Vector2>& Parabola::GetResult2D() const
{
	return Result2D;
}

const std::vector<Vector3>& Parabola::GetResult3D() const
{
	return Result3D;
}

constexpr float Parabola::Deg2Rad(float Degree)
{
	return Degree * (M_PI / 180.0f);
}

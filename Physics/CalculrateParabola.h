#pragma once

#include <vector>
#include <memory>

struct Vector2
{
	float x;
	float y;
};

struct Vector3
{
	float x;
	float y;
	float z;
};

class Parabola
{
public:

	Parabola() = default;
	~Parabola() = default;

	void CalculateParabola2D(const Vector2& Origin, float Degree, float StartVelocity, float TickInterval);
	void CalculateParabola3D(const Vector3& Origin, const Vector3& Degree, float StartVelocity, float TickInterval);

	const std::vector<Vector2>& GetResult2D() const;
	const std::vector<Vector3>& GetResult3D() const;

private:

	constexpr float Deg2Rad(float Degree);

private:

	std::vector<Vector2> Result2D;
	std::vector<Vector3> Result3D;

};

#pragma once

// Use SSE2
#include <emmintrin.h>

class Vector4
{
public:

	float X;
	float Y;
	float Z;
	float W;

public:

	explicit Vector4() noexcept;
	explicit Vector4(float InX, float InY, float InZ, float InW) noexcept;
	~Vector4() = default;

	float DotProduct(const Vector4& InVector);
	Vector4 CrossProduct(const Vector4& InVector);

	Vector4 operator+(const Vector4& InVector);
	Vector4 operator-(const Vector4& InVector);
	Vector4 operator*(float InScalar);
	friend Vector4 operator*(float InScalar, const Vector4& InVector);

};


class Float4
{
public:

	__m128 Data;

public:

	explicit Float4() noexcept;
	explicit Float4(float InX, float InY, float InZ, float InW) noexcept;
	explicit Float4(__m128 InData) noexcept;

	Float4 DotProduct(Float4 InVector);
	Float4 CrossProduct(Float4 InVector);

	Float4 operator+(Float4 InVector);
	Float4 operator-(Float4 InVector);
	Float4 operator*(Float4 InScalar);

};

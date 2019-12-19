#include "Vector4.h"

Vector4::Vector4() noexcept
	: X(0)
	, Y(0)
	, Z(0)
	, W(0)
{
}

Vector4::Vector4(float InX, float InY, float InZ, float InW) noexcept
	: X(InX)
	, Y(InY)
	, Z(InZ)
	, W(InW)
{
}

float Vector4::DotProduct(const Vector4& InVector)
{
	return X * InVector.X + Y * InVector.Y + Z * InVector.Z;
}

Vector4 Vector4::CrossProduct(const Vector4& InVector)
{
	Vector4 OutVector;

	OutVector.X = Y * InVector.Z - Z * InVector.Y;
	OutVector.Y = Z * InVector.X - X * InVector.Z;
	OutVector.Z = X * InVector.Y - Y * InVector.X;
	OutVector.W = 0.0f;

	return OutVector;
}

Vector4 Vector4::operator+(const Vector4& InVector)
{
	Vector4 OutVector;

	OutVector.X = X + InVector.X;
	OutVector.Y = Y + InVector.Y;
	OutVector.Z = Z + InVector.Z;
	OutVector.W = 0.0f;

	return OutVector;
}

Vector4 Vector4::operator-(const Vector4& InVector)
{
	Vector4 OutVector;

	OutVector.X = X - InVector.X;
	OutVector.Y = Y - InVector.Y;
	OutVector.Z = Z - InVector.Z;
	OutVector.W = 0.0f;

	return OutVector;
}

Vector4 Vector4::operator*(float InScalar)
{
	Vector4 OutVector;

	OutVector.X = X * InScalar;
	OutVector.Y = Y * InScalar;
	OutVector.Z = Z * InScalar;
	OutVector.W = 0.0f;

	return OutVector;
}

Vector4 operator*(float InScalar, const Vector4& InVector)
{
	Vector4 OutVector;

	OutVector.X = InVector.X * InScalar;
	OutVector.Y = InVector.Y * InScalar;
	OutVector.Z = InVector.Z * InScalar;
	OutVector.W = 0.0f;

	return OutVector;
}

Float4::Float4() noexcept
	: Data(_mm_setzero_ps())
{
}

Float4::Float4(float InX, float InY, float InZ, float InW) noexcept
	: Data(_mm_set_ps(InX, InY, InZ, InW))
{
}

Float4::Float4(__m128 InData) noexcept
	: Data(InData)
{
}

Float4 Float4::DotProduct(Float4 InVector)
{
	__m128 MulData;
	__m128 SumData;
	MulData = _mm_mul_ps(Data, InVector.Data);

	SumData = _mm_add_ps(
		_mm_add_ps(
		_mm_shuffle_ps(MulData, MulData, _MM_SHUFFLE(0, 0, 0, 0)),
		_mm_shuffle_ps(MulData, MulData, _MM_SHUFFLE(1, 1, 1, 1))), 
		_mm_add_ps(
		_mm_shuffle_ps(MulData, MulData, _MM_SHUFFLE(2, 2, 2, 2)),
		_mm_shuffle_ps(MulData, MulData, _MM_SHUFFLE(3, 3, 3, 3))));

	return Float4(SumData);
}

Float4 Float4::CrossProduct(Float4 InVector)
{
	__m128 ShuffleData1;
	__m128 ShuffleData2;
	__m128 OutData;
	ShuffleData1 = _mm_shuffle_ps(Data, Data, _MM_SHUFFLE(3, 0, 2, 1));
	ShuffleData2 = _mm_shuffle_ps(InVector.Data, InVector.Data, _MM_SHUFFLE(3, 0, 2, 1));
	ShuffleData1 = _mm_mul_ps(ShuffleData1, Data);
	ShuffleData2 = _mm_mul_ps(ShuffleData2, InVector.Data);

	OutData = _mm_sub_ps(ShuffleData1, ShuffleData2);
	OutData = _mm_shuffle_ps(OutData, OutData, _MM_SHUFFLE(3, 0, 2, 1));

	return Float4(OutData);
}

Float4 Float4::operator+(Float4 InVector)
{
	return Float4(_mm_add_ps(Data, InVector.Data));
}

Float4 Float4::operator-(Float4 InVector)
{
	return Float4(_mm_sub_ps(Data, InVector.Data));
}

Float4 Float4::operator*(Float4 InScalar)
{
	return Float4(_mm_mul_ps(Data, InScalar.Data));
}

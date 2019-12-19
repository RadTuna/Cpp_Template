
#ifdef _DEBUG
#pragma comment(lib, "benchmark_d.lib")
#elif NDEBUG
#pragma comment(lib, "benchmark.lib")
#endif

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Container")

#include "benchmark.h"
#include "Vector4.h"

static void BM_Vector4_ADD_withoutSIMD(benchmark::State& state)
{
	Vector4 V1(1.0f, 2.0f, 3.0f, 4.0f);
	Vector4 V2(1.0f, 2.0f, 3.0f, 4.0f);
	while (state.KeepRunning())
	{
		for (int i = 0; i < state.range_x(); ++i)
		{
			for (int j = 0; j < state.range_x(); ++j)
			{
				V2 = V1 + V2;
			}
		}
	}
}
BENCHMARK(BM_Vector4_ADD_withoutSIMD)->Range(1 << 4, 1 << 8);

static void BM_Float4_ADD_withSIMD(benchmark::State& state)
{
	Float4 F1(1.0f, 2.0f, 3.0f, 4.0f);
	Float4 F2(1.0f, 2.0f, 3.0f, 4.0f);
	while (state.KeepRunning())
	{
		for (int i = 0; i < state.range_x(); ++i)
		{
			for (int j = 0; j < state.range_x(); ++j)
			{
				F2 = F1 + F2;
			}
		}
	}
}
BENCHMARK(BM_Float4_ADD_withSIMD)->Range(1 << 4, 1 << 8);

static void BM_Vector4_Cross_withoutSIMD(benchmark::State& state)
{
	Vector4 V1(1.0f, 2.0f, 3.0f, 4.0f);
	Vector4 V2(1.0f, 2.0f, 3.0f, 4.0f);
	while (state.KeepRunning())
	{
		for (int i = 0; i < state.range_x(); ++i)
		{
			for (int j = 0; j < state.range_x(); ++j)
			{
				V2 = V1.CrossProduct(V2);
			}
		}
	}
}
BENCHMARK(BM_Vector4_Cross_withoutSIMD)->Range(1 << 4, 1 << 8);

static void BM_Float4_Cross_withSIMD(benchmark::State& state)
{
	Float4 F1(1.0f, 2.0f, 3.0f, 4.0f);
	Float4 F2(1.0f, 2.0f, 3.0f, 4.0f);
	while (state.KeepRunning())
	{
		for (int i = 0; i < state.range_x(); ++i)
		{
			for (int j = 0; j < state.range_x(); ++j)
			{
				F2 = F1.CrossProduct(F2);
			}
		}
	}
}
BENCHMARK(BM_Float4_Cross_withSIMD)->Range(1 << 4, 1 << 8);


BENCHMARK_MAIN();

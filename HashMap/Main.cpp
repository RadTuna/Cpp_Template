#include <iostream>
#include <ctime>
#include "HashMap.h"

using namespace std;

// HashMap�� �׽�Ʈ�ϴ� �׽�Ʈ Main�Լ�.
int main()
{
	constexpr int MaxLoad = 1000;

	static int ConflictCount = 0;

	srand(static_cast<unsigned int>(time(nullptr)));

	HashMap<int, int> MyMap;
	for (int i = 0; i < MaxLoad; ++i)
	{
		int randVal = rand() % MaxLoad;
		if (MyMap.Add(randVal, randVal) == false)
		{
			ConflictCount++;
		}
	}

	cout << "Conflict : " << ConflictCount << endl;

	cout << "LoadRatio : " << MyMap.GetLoadRatio() << endl;

	return 0;
}
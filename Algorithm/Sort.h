#pragma once

#include <queue>

class Sort
{
public:

	Sort() = delete;
	~Sort() = delete;

	/*
	@ param keyArr : 키값을 가지는 배열. 일반적으로 int 자료형 사용을 권장함.
	@ param valArr : 데이터값을 가지는 배열. 키배열과 매칭이 되어야 함.
	@ param keyArrLen : 키배열의 길이. 데이터배열의 길이와 같아야함.
	@ param valArrLen : 데이터배열의 길이. 키배열의 길이와 같아야함.
	@ param maxKey : 키배열의 값중에 가장 큰 값. 기수정렬 자리수 검출에 사용됨.
	@ return : 키배열길이와 데이터배열길이가 다르면 false반환. 그외의 경우에는 true반환.
	*/
	// LSD RadixSort를 구현한 함수입니다. Key값에 맞춰서 Value값도 정렬하여 반환합니다.
	template<typename Key = int, typename Val>
	static bool RadixSort(Key* keyArr, Val* valArr, int keyArrLen, int valArrLen, int maxKey);

	/*
	@ param keyArr : 키값을 가지는 배열. 일반적으로 int 자료형 사용을 권장함.
	@ param keyArrLen : 키배열의 길이
	@ param maxKey : 키배열의 값중에 가장 큰 값. 기수정렬 자리수 검출에 사용됨.
	*/
	// LSD RadixSort를 구현한 함수입니다. Key값을 정렬하여 반환합니다. (Essential Ver)
	template<typename Key = int>
	static void RadixSortEs(Key* keyArr, int keyArrLen, int maxKey);

private:
};

// LSD RadixSort 구현.
template<typename Key, typename Val>
bool Sort::RadixSort(Key* keyArr, Val* valArr, int keyArrLen, int valArrLen, int maxKey)
{
	if (keyArrLen != valArrLen)
	{
		return false;
	}

	enum { BUCKET_SIZE = 10 };

	std::queue<Key> bucketList[BUCKET_SIZE];

	// 밑의 Value의 정렬을 위해 필요함.
	Key* altKeyArr = new Key[keyArrLen];
	for (int i = 0; i < keyArrLen; ++i)
	{
		altKeyArr[i] = keyArr[i];
	}

	// keyArr에서 가장 큰수의 자릿수를 구함.
	int PosNumCount = 1;
	for (int i = 10;; i *= 10, ++PosNumCount)
	{
		if (maxKey % i >= maxKey)
		{
			break;
		}
	}

	// keyArr에 대한 기수정렬을 시작함.
	for (int i = 1; i <= PosNumCount; ++i)
	{
		// 기수 버킷에 key값을 집어 넣음.
		for (int j = 0; j < keyArrLen; ++j)
		{
			int powNum = static_cast<int>(std::pow(10, i));
			bucketList[(keyArr[j] % powNum) / (powNum / 10)].push(keyArr[j]);
		}
		
		// 기수 버킷에서 keyArr로 되돌려 놓음.
		int keyArrCount = 0;
		for (int j = 0; j < BUCKET_SIZE; ++j)
		{
			if (bucketList[j].empty() == true)
			{
				continue;
			}

			for (;bucketList[j].empty() == false;)
			{
				keyArr[keyArrCount] = bucketList[j].front();
				bucketList[j].pop();
				++keyArrCount;
			}
		}
	}
	
	// valArr의 정렬을 위해 복사본 배열을 생성함.
	// 왜인지는 모르겠지만, 템플릿에서 정적배열 선언이 안됨.
	Val* altValArr = new Val[valArrLen];
	for (int i = 0; i < valArrLen; ++i)
	{
		altValArr[i] = valArr[i];
	}

	// keyArr에 따라 valArr을 정렬함.
	for (int i = 0; i < valArrLen; ++i)
	{
		valArr[altKeyArr[i]] = altValArr[keyArr[i]];
	}

	delete[] altValArr;
	altValArr = nullptr;

	delete[] altKeyArr;
	altKeyArr = nullptr;

	return true;
}

// LSD RadixSort 구현. (Essential Ver)
template<typename Key>
inline void Sort::RadixSortEs(Key* keyArr, int keyArrLen, int maxKey)
{
	enum { BUCKET_SIZE = 10 };

	std::queue<Key> bucketList[BUCKET_SIZE];

	// keyArr에서 가장 큰수의 자릿수를 구함.
	int PosNumCount = 1;
	for (int i = 10;; i *= 10, ++PosNumCount)
	{
		if (maxKey % i >= maxKey)
		{
			break;
		}
	}

	// keyArr에 대한 기수정렬을 시작함.
	for (int i = 1; i <= PosNumCount; ++i)
	{
		// 기수 버킷에 key값을 집어 넣음.
		for (int j = 0; j < keyArrLen; ++j)
		{
			int powNum = static_cast<int>(std::pow(10, i));
			bucketList[(keyArr[j] % powNum) / (powNum / 10)].push(keyArr[j]);
		}

		// 기수 버킷에서 keyArr로 되돌려 놓음.
		int keyArrCount = 0;
		for (int j = 0; j < BUCKET_SIZE; ++j)
		{
			if (bucketList[j].empty() == true)
			{
				continue;
			}

			for (; bucketList[j].empty() == false;)
			{
				keyArr[keyArrCount] = bucketList[j].front();
				bucketList[j].pop();
				++keyArrCount;
			}
		}
	}
}



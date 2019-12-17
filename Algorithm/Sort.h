#pragma once

#include <queue>

class Sort
{
public:

	Sort() = delete;
	~Sort() = delete;

	/*
	@ param keyArr : Ű���� ������ �迭. �Ϲ������� int �ڷ��� ����� ������.
	@ param valArr : �����Ͱ��� ������ �迭. Ű�迭�� ��Ī�� �Ǿ�� ��.
	@ param keyArrLen : Ű�迭�� ����. �����͹迭�� ���̿� ���ƾ���.
	@ param valArrLen : �����͹迭�� ����. Ű�迭�� ���̿� ���ƾ���.
	@ param maxKey : Ű�迭�� ���߿� ���� ū ��. ������� �ڸ��� ���⿡ ����.
	@ return : Ű�迭���̿� �����͹迭���̰� �ٸ��� false��ȯ. �׿��� ��쿡�� true��ȯ.
	*/
	// LSD RadixSort�� ������ �Լ��Դϴ�. Key���� ���缭 Value���� �����Ͽ� ��ȯ�մϴ�.
	template<typename Key = int, typename Val>
	static bool RadixSort(Key* keyArr, Val* valArr, int keyArrLen, int valArrLen, int maxKey);

	/*
	@ param keyArr : Ű���� ������ �迭. �Ϲ������� int �ڷ��� ����� ������.
	@ param keyArrLen : Ű�迭�� ����
	@ param maxKey : Ű�迭�� ���߿� ���� ū ��. ������� �ڸ��� ���⿡ ����.
	*/
	// LSD RadixSort�� ������ �Լ��Դϴ�. Key���� �����Ͽ� ��ȯ�մϴ�. (Essential Ver)
	template<typename Key = int>
	static void RadixSortEs(Key* keyArr, int keyArrLen, int maxKey);

private:
};

// LSD RadixSort ����.
template<typename Key, typename Val>
bool Sort::RadixSort(Key* keyArr, Val* valArr, int keyArrLen, int valArrLen, int maxKey)
{
	if (keyArrLen != valArrLen)
	{
		return false;
	}

	enum { BUCKET_SIZE = 10 };

	std::queue<Key> bucketList[BUCKET_SIZE];

	// ���� Value�� ������ ���� �ʿ���.
	Key* altKeyArr = new Key[keyArrLen];
	for (int i = 0; i < keyArrLen; ++i)
	{
		altKeyArr[i] = keyArr[i];
	}

	// keyArr���� ���� ū���� �ڸ����� ����.
	int PosNumCount = 1;
	for (int i = 10;; i *= 10, ++PosNumCount)
	{
		if (maxKey % i >= maxKey)
		{
			break;
		}
	}

	// keyArr�� ���� ��������� ������.
	for (int i = 1; i <= PosNumCount; ++i)
	{
		// ��� ��Ŷ�� key���� ���� ����.
		for (int j = 0; j < keyArrLen; ++j)
		{
			int powNum = static_cast<int>(std::pow(10, i));
			bucketList[(keyArr[j] % powNum) / (powNum / 10)].push(keyArr[j]);
		}
		
		// ��� ��Ŷ���� keyArr�� �ǵ��� ����.
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
	
	// valArr�� ������ ���� ���纻 �迭�� ������.
	// �������� �𸣰�����, ���ø����� �����迭 ������ �ȵ�.
	Val* altValArr = new Val[valArrLen];
	for (int i = 0; i < valArrLen; ++i)
	{
		altValArr[i] = valArr[i];
	}

	// keyArr�� ���� valArr�� ������.
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

// LSD RadixSort ����. (Essential Ver)
template<typename Key>
inline void Sort::RadixSortEs(Key* keyArr, int keyArrLen, int maxKey)
{
	enum { BUCKET_SIZE = 10 };

	std::queue<Key> bucketList[BUCKET_SIZE];

	// keyArr���� ���� ū���� �ڸ����� ����.
	int PosNumCount = 1;
	for (int i = 10;; i *= 10, ++PosNumCount)
	{
		if (maxKey % i >= maxKey)
		{
			break;
		}
	}

	// keyArr�� ���� ��������� ������.
	for (int i = 1; i <= PosNumCount; ++i)
	{
		// ��� ��Ŷ�� key���� ���� ����.
		for (int j = 0; j < keyArrLen; ++j)
		{
			int powNum = static_cast<int>(std::pow(10, i));
			bucketList[(keyArr[j] % powNum) / (powNum / 10)].push(keyArr[j]);
		}

		// ��� ��Ŷ���� keyArr�� �ǵ��� ����.
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



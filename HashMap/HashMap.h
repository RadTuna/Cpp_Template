#pragma once

#include <iostream>

enum { defaultReserve = 557, maxiamDepth = 1000 };

// 해당 해쉬맵은 Modular Hashing을 사용한 해쉬맵입니다.
// 해쉬 충돌이 발생할 경우 해당 버킷에 링크드리스트 구조를 만들어 회피합니다. (싱글 링크 사용)
template<typename V, typename K>
class HashMapBase
{
private:

	struct Data
	{

		K key;
		V value;
		Data* nextData;

		Data(K key, V value) : key(key), value(value), nextData(nullptr) {}
		Data(const Data& other) : key(other.key), value(other.value), nextData(nullptr) {}

	};

public:

	HashMapBase();
	HashMapBase(int reserve);
	HashMapBase(const HashMapBase& other) = delete;
	~HashMapBase();
	HashMapBase& operator=(const HashMapBase& other) = delete;

	/*
	@ key : 입력되는 해쉬 키 입니다.
	@ value : 입력 되는 데이터 입니다.
	@ return : 해쉬 충돌이 없으면 true, 충돌로 인해 링크드 리스트로 저장되었으면 false.
	*/
	// 해쉬키에 따라 버킷에 쌍으로 저장하는 함수입니다.
	bool Add(K key, V value);

	/*
	@ key : 입력되는 해쉬 키 입니다.
	@ return : 제거에 성공했으면 true, 실패했으면 false.
	*/
	// 해쉬 키에 맞는 노드를 제거합니다.
	bool Remove(K key);

	/*
	@ key : 입력되는 해쉬 키 입니다.
	@ outValue
	*/
	bool GetValue(K key, V* outValue);

	// 버킷의 적재율을 반환하는 함수입니다. 링크드리스트는 포함하지 않습니다.
	float GetLoadRatio();

private:

	/*
	@ key : 입력된 해쉬 키 입니다.
	@ return : 해싱 함수를 거친 배열 인덱스 입니다.
	*/
	// 해쉬 키를 배열 인덱스로 변환하는 해싱함수 입니다.
	virtual unsigned int GetHashIndex(K key);

	/*
	@ index : 탐색을 원하는 배열의 인덱스를 입력합니다.
	@ outPtr : 해당 배열의 링크드 리스트의 마지막 노드의 포인터를 반환합니다.
	@ return : 링크드 리스트의 Depth가 1000 이상이면 종료하고 false를 반환합니다.
	*/
	// 해쉬맵 단일 버킷의 링크드 리스트 마지막 노드를 반환하는 함수
	bool GetLastData(int index, Data** outPtr);

	/*
	@ prevNode : 링크드 리스트의 이전 노드를 입력합니다.
	@ curNode : 링크드 리스트의 현재 노드를 입력합니다.
	*/
	// 링크드 리스트 구조에서 중간노드를 제거할 때 호출합니다.
	void LinkRemove(Data* prevNode, Data* curNode);

	// dataArr을 nullptr로 초기화하는 함수입니다.
	void InitializeArray();

protected:

	Data** dataArr;
	int bucketSize;
	static const unsigned __int64 FNVOffset = 14695981039346656037;
	static const unsigned __int64 FNVPrime = 1099511628211;

public:

	inline int GetBucketSize() const { return bucketSize; }

};

template<typename V, typename K>
class HashMap : public HashMapBase<V, K>
{
public:

	HashMap() : HashMapBase<V, K>() {}
	HashMap(int reserve) : HashMapBase<V, K>(reserve) {}
	~HashMap() = default;

};

template<typename V>
class HashMap<V, char*> : public HashMapBase<V, char*>
{
public:

	HashMap() : HashMapBase<V, char*>() {}
	HashMap(int reserve) : HashMapBase<V, char*>(reserve) {}
	~HashMap() = default;

private:

	unsigned int GetHashIndex(char* key) override;

};

template<typename V, typename K>
HashMapBase<V, K>::HashMapBase()
	: bucketSize(defaultReserve)
{
	dataArr = new Data*[defaultReserve];

	InitializeArray();
}

template<typename V, typename K>
HashMapBase<V, K>::HashMapBase(int reserve)
	: bucketSize(reserve)
{
	dataArr = new Data*[reserve];

	InitializeArray();
}

template<typename V, typename K>
HashMapBase<V, K>::~HashMapBase()
{
	if (dataArr != nullptr)
	{
		delete[] dataArr;
		dataArr = nullptr;
	}
}

template<typename V, typename K>
bool HashMapBase<V, K>::Add(K key, V value)
{
	unsigned int index = GetHashIndex(key);

	if (dataArr[index] == nullptr)
	{
		dataArr[index] = new Data(key, value);

		return true;
	}
	else
	{
		Data* lastNode = nullptr;
		GetLastData(index, &lastNode);

		Data* linkData = new Data(key, value);
		lastNode->nextData = linkData;

		return false;
	}

	return false;
}

template<typename V, typename K>
bool HashMapBase<V, K>::Remove(K key)
{
	unsigned int index = GetHashIndex(key);

	if (dataArr[index] == nullptr) // 해당 해쉬 키의 버킷에 데이터가 없음.
	{
		return false;
	}

	if (dataArr[index]->key != key)
	{
		Data* prevPtr = dataArr[index];
		Data* curPtr = prevPtr->nextData;

		for (int i = 0; i < maxiamDepth; ++i)
		{
			if (curPtr == nullptr)
			{
				return false;
			}

			if (curPtr->key == key)
			{
				LinkRemove(prevPtr, curPtr);
				return true;
			}
			else
			{
				prevPtr = curPtr;
				curPtr = curPtr->nextData;
			}
		}
	}
	else
	{
		if (dataArr[index]->nextData == nullptr)
		{
			delete dataArr[index];
			dataArr[index] = nullptr;
		}
		else
		{
			Data* tempPtr = dataArr[index];
			dataArr[index] = dataArr[index]->nextData;
			delete tempPtr;
			tempPtr = nullptr;
		}

		return true;
	}

	// 링크드 리스크 Depth탐색을 1000이상 진행한 경우.
	return false;
}

template<typename V, typename K>
bool HashMapBase<V, K>::GetValue(K key, V* outValue)
{
	unsigned int index = GetHashIndex(key);

	if (dataArr[index] == nullptr) // 해당 해쉬 키의 버킷에 데이터가 없음.
	{
		return false;
	}

	if (dataArr[index]->key != key)
	{
		Data* prevPtr = dataArr[index];
		Data* curPtr = prevPtr->nextData;

		for (int i = 0; i < maxiamDepth; ++i)
		{
			if (curPtr == nullptr)
			{
				return false;
			}

			if (curPtr->key == key)
			{
				*outValue = curPtr->value;
				return true;
			}
			else
			{
				prevPtr = curPtr;
				curPtr = curPtr->nextData;
			}
		}
	}
	else
	{
		*outValue = dataArr[index]->value;
		return true;
	}

	// 링크드 리스트 탐색을 1000이상 진행한 경우
	return false;
}

template<typename V, typename K>
float HashMapBase<V, K>::GetLoadRatio()
{
	int loadCount = 0;

	for (int i = 0; i < bucketSize; ++i)
	{
		if (dataArr[i] != nullptr)
		{
			++loadCount;
		}
	}

	float result = (static_cast<float>(loadCount) / static_cast<float>(bucketSize)) * 100.0f;

	return result;
}

template<typename V, typename K>
unsigned int HashMapBase<V, K>::GetHashIndex(K key)
{
	unsigned __int64 conKey = (unsigned __int64)key;
	unsigned __int64 hash = FNVOffset;
	for (unsigned __int8 bytehash = static_cast<unsigned __int8>(conKey); bytehash > 0;)
	{
		hash *= FNVPrime;
		hash ^= bytehash;

		conKey = conKey >> 8;
		bytehash = static_cast<unsigned __int8>(conKey);
	}

	return hash % bucketSize;
}

template<typename V, typename K>
bool HashMapBase<V, K>::GetLastData(int index, Data** outPtr)
{
	Data* curPtr = dataArr[index];

	for (int i = 0; i < maxiamDepth; ++i)
	{
		if (curPtr->nextData == nullptr)
		{
			*outPtr = curPtr;
			return true;
		}
		else
		{
			curPtr = curPtr->nextData;
		}
	}

	return false;
}

template<typename V, typename K>
void HashMapBase<V, K>::LinkRemove(Data* prevNode, Data* curNode)
{
	if (curNode->nextData == nullptr)
	{
		prevNode->nextData = nullptr;
		delete curNode;
		curNode = nullptr;
	}
	else
	{
		prevNode->nextData = curNode->nextData;
		delete curNode;
		curNode = nullptr;
	}
}

template<typename V, typename K>
void HashMapBase<V, K>::InitializeArray()
{
	for (int i = 0; i < bucketSize; ++i)
	{
		dataArr[i] = nullptr;
	}
}

template<typename V>
unsigned int HashMap<V, char*>::GetHashIndex(char* key)
{
	unsigned __int64 conKey = (unsigned __int64)key;
	unsigned __int64 hash = HashMapBase<V, char*>::FNVOffset;
	
	int stringLen = strlen(key);
	for (int i = 0; i < stringLen; ++i)
	{
		unsigned __int8 bytehash = static_cast<unsigned __int8>(key[i]);

		hash *= HashMapBase<V, char*>::FNVPrime;
		hash ^= bytehash;
	}

	return hash % HashMapBase<V, char*>::bucketSize;

	return 0;
}

#pragma once

enum { defaultReserve = 557, maxiamDepth = 1000 };

// �ش� �ؽ����� Modular Hashing�� ����� �ؽ����Դϴ�.
// �ؽ� �浹�� �߻��� ��� �ش� ��Ŷ�� ��ũ�帮��Ʈ ������ ����� ȸ���մϴ�. (�̱� ��ũ ���)
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
	@ key : �ԷµǴ� �ؽ� Ű �Դϴ�.
	@ value : �Է� �Ǵ� ������ �Դϴ�.
	@ return : �ؽ� �浹�� ������ true, �浹�� ���� ��ũ�� ����Ʈ�� ����Ǿ����� false.
	*/
	// �ؽ�Ű�� ���� ��Ŷ�� ������ �����ϴ� �Լ��Դϴ�.
	bool Add(K key, V value);

	/*
	@ key : �ԷµǴ� �ؽ� Ű �Դϴ�.
	@ return : ���ſ� ���������� true, ���������� false.
	*/
	// �ؽ� Ű�� �´� ��带 �����մϴ�.
	bool Remove(K key);

	/*
	@ key : �ԷµǴ� �ؽ� Ű �Դϴ�.
	@ outValue
	*/
	bool GetValue(K key, V* outValue);

	// ��Ŷ�� �������� ��ȯ�ϴ� �Լ��Դϴ�. ��ũ�帮��Ʈ�� �������� �ʽ��ϴ�.
	float GetLoadRatio();

private:

	/*
	@ key : �Էµ� �ؽ� Ű �Դϴ�.
	@ return : �ؽ� �Լ��� ��ģ �迭 �ε��� �Դϴ�.
	*/
	// �ؽ� Ű�� �迭 �ε����� ��ȯ�ϴ� �ؽ��Լ� �Դϴ�.
	virtual unsigned int GetHashIndex(K key);

	/*
	@ index : Ž���� ���ϴ� �迭�� �ε����� �Է��մϴ�.
	@ outPtr : �ش� �迭�� ��ũ�� ����Ʈ�� ������ ����� �����͸� ��ȯ�մϴ�.
	@ return : ��ũ�� ����Ʈ�� Depth�� 1000 �̻��̸� �����ϰ� false�� ��ȯ�մϴ�.
	*/
	// �ؽ��� ���� ��Ŷ�� ��ũ�� ����Ʈ ������ ��带 ��ȯ�ϴ� �Լ�
	bool GetLastData(int index, Data** outPtr);

	/*
	@ prevNode : ��ũ�� ����Ʈ�� ���� ��带 �Է��մϴ�.
	@ curNode : ��ũ�� ����Ʈ�� ���� ��带 �Է��մϴ�.
	*/
	// ��ũ�� ����Ʈ �������� �߰���带 ������ �� ȣ���մϴ�.
	void LinkRemove(Data* prevNode, Data* curNode);

	// dataArr�� nullptr�� �ʱ�ȭ�ϴ� �Լ��Դϴ�.
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

	if (dataArr[index] == nullptr) // �ش� �ؽ� Ű�� ��Ŷ�� �����Ͱ� ����.
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

	// ��ũ�� ����ũ DepthŽ���� 1000�̻� ������ ���.
	return false;
}

template<typename V, typename K>
bool HashMapBase<V, K>::GetValue(K key, V* outValue)
{
	unsigned int index = GetHashIndex(key);

	if (dataArr[index] == nullptr) // �ش� �ؽ� Ű�� ��Ŷ�� �����Ͱ� ����.
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

	// ��ũ�� ����Ʈ Ž���� 1000�̻� ������ ���
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

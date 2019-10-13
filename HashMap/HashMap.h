#pragma once

enum { defaultReserve = 557, maxiamDepth = 1000 };

// �ش� �ؽ����� Modular Hashing�� ����� �ؽ����Դϴ�.
// �ؽ� �浹�� �߻��� ��� �ش� ��Ŷ�� ��ũ�帮��Ʈ ������ ����� ȸ���մϴ�. (�̱� ��ũ ���)
template<typename K, typename V>
class HashMap
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

	HashMap();
	HashMap(int reserve);
	HashMap(const HashMap& other) = delete;
	~HashMap();
	HashMap& operator=(const HashMap& other) = delete;

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
	float GetLoadRatio();

private:

	/*
	@ key : �Էµ� �ؽ� Ű �Դϴ�.
	@ return : �ؽ� �Լ��� ��ģ �迭 �ε��� �Դϴ�.
	*/
	// �ؽ� Ű�� �迭 �ε����� ��ȯ�ϴ� �ؽ��Լ� �Դϴ�.
	int GetHashIndex(K key);

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

private:

	Data** dataArr;
	int bucketSize;

public:

	inline int GetBucketSize() const { return bucketSize; }

};



template<typename K, typename V>
HashMap<K, V>::HashMap()
	: bucketSize(defaultReserve)
{
	dataArr = new Data*[defaultReserve];

	InitializeArray();
}

template<typename K, typename V>
HashMap<K, V>::HashMap(int reserve)
	: bucketSize(reserve)
{
	dataArr = new Data*[reserve];

	InitializeArray();
}

template<typename K, typename V>
HashMap<K, V>::~HashMap()
{
	if (dataArr != nullptr)
	{
		delete[] dataArr;
		dataArr = nullptr;
	}
}

template<typename K, typename V>
bool HashMap<K, V>::Add(K key, V value)
{
	int index = GetHashIndex(key);

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

template<typename K, typename V>
bool HashMap<K, V>::Remove(K key)
{
	int index = GetHashIndex(key);

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

template<typename K, typename V>
bool HashMap<K, V>::GetValue(K key, V* outValue)
{
	int index = GetHashIndex(key);

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

template<typename K, typename V>
float HashMap<K, V>::GetLoadRatio()
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

template<typename K, typename V>
int HashMap<K, V>::GetHashIndex(K key)
{
	int conKey = (int)key;

	return conKey % bucketSize;
}

template<typename K, typename V>
bool HashMap<K, V>::GetLastData(int index, Data** outPtr)
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

template<typename K, typename V>
void HashMap<K, V>::LinkRemove(Data* prevNode, Data* curNode)
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

template<typename K, typename V>
void HashMap<K, V>::InitializeArray()
{
	for (int i = 0; i < bucketSize; ++i)
	{
		dataArr[i] = nullptr;
	}
}


#pragma once

// Array based BinarySearchTree

template<typename T>
struct DefaultComparer
{
	bool operator()(const T& ValueA, const T& ValueB)
	{
		return ValueA < ValueB;
	}
};

template<typename K, typename D>
struct Node
{
	K Key;
	D Data;
	bool IsFill;

	Node() : Key(), Data(), IsFill(false) {}
};

template<typename K, typename D, typename Com = DefaultComparer<K>>
class BinarySerchTree
{
public:

	BinarySerchTree();
	BinarySerchTree(unsigned int InitDepth);
	~BinarySerchTree();

	bool InsertNode(const K& InKey, const D& InData, unsigned int Index = 1);
	bool EraseNode(const K& InKey);
	bool TryGetData(const K& InKey, D& OutData);

private:

	void InitTreeArray(unsigned int InDepth);
	Node<K, D>* GetNode(const K& InKey, unsigned int& OutIndex, unsigned int Index = 1);
	Node<K, D>* GetMinNode(unsigned int Index = 1);
	Node<K, D>* GetMaxNode(unsigned int Index = 1);
	void CopySubTree(unsigned int OriginIndex, unsigned int TargetIndex);

private:

	enum { DEFAULT_TREE_DEPTH = 4 };

	unsigned int TreeDepth;
	unsigned int ArrayCapacity;
	Node<K, D>* TreeArray;
	Com Comparer;

};

template<typename K, typename D, typename Com>
BinarySerchTree<K, D, Com>::BinarySerchTree()
	: TreeDepth(DEFAULT_TREE_DEPTH)
	, TreeArray(nullptr)
	, ArrayCapacity(2 << DEFAULT_TREE_DEPTH)
{
	InitTreeArray(TreeDepth);
}

template<typename K, typename D, typename Com>
BinarySerchTree<K, D, Com>::BinarySerchTree(unsigned int InitDepth)
	: TreeDepth(InitDepth)
	, TreeArray(nullptr)
	, ArrayCapacity(2 << InitDepth)
{
	InitTreeArray(TreeDepth);
}

template<typename K, typename D, typename Com>
BinarySerchTree<K, D, Com>::~BinarySerchTree()
{
	if (TreeArray != nullptr)
	{
		delete[] TreeArray;
		TreeArray = nullptr;
	}
}

template<typename K, typename D, typename Com>
bool BinarySerchTree<K, D, Com>::InsertNode(const K& InKey, const D& InData, unsigned int Index)
{
	if (Index >= ArrayCapacity)
	{
		InitTreeArray(TreeDepth * 2);
	}

	if (TreeArray[Index].Key == InKey)
	{
		return false;
	}
	if (TreeArray[Index].IsFill == false)
	{
		TreeArray[Index].Key = InKey;
		TreeArray[Index].Data = InData;
		TreeArray[Index].IsFill = true;
		return true;
	}
	if (Comparer(TreeArray[Index].Key, InKey) == true)
	{
		return InsertNode(InKey, InData, Index * 2);
	}
	else
	{
		return InsertNode(InKey, InData, Index * 2 + 1);
	}
}

template<typename K, typename D, typename Com>
bool BinarySerchTree<K, D, Com>::EraseNode(const K& InKey)
{
	unsigned int FindNodeIndex = 0U;
	Node<K, D>* FindNode = GetNode(InKey, FindNodeIndex);

	if (FindNode == nullptr)
	{
		return false;
	}
	
	// 트리가 끝났으므로 무조건 말단노드임.
	if (FindNodeIndex * 2 > ArrayCapacity || (TreeArray[FindNodeIndex * 2].IsFill == false && TreeArray[FindNodeIndex * 2 + 1].IsFill == false))
	{
		FindNode->Key = K();
		FindNode->Data = D();
		FindNode->IsFill = false;
		return true;
	}
	else if (TreeArray[FindNodeIndex * 2].IsFill == true && TreeArray[FindNodeIndex * 2 + 1].IsFill == true)
	{
		Node<K, D>* OtherFindNode = GetMaxNode(FindNodeIndex * 2);

		*FindNode = *OtherFindNode;
		OtherFindNode->Key = K();
		OtherFindNode->Data = D();
		OtherFindNode->IsFill = false;
		return true;
	}
	else
	{
		unsigned int OtherIndex = TreeArray[FindNodeIndex * 2].IsFill ? FindNodeIndex * 2 : OtherIndex = FindNodeIndex * 2 + 1;
		CopySubTree(OtherIndex, FindNodeIndex);
		return true;
	}
}

template<typename K, typename D, typename Com>
bool BinarySerchTree<K, D, Com>::TryGetData(const K& InKey, D& OutData)
{
	unsigned int Dummy;
	Node<K, D>* FindNode = GetNode(InKey, Dummy);

	if (FindNode == nullptr)
	{
		return false;
	}
	else
	{
		OutData = FindNode->Data;
		return true;
	}
}

template<typename K, typename D, typename Com>
void BinarySerchTree<K, D, Com>::InitTreeArray(unsigned int InDepth)
{
	Node<K, D>* NewTreeArray = new Node<K, D>[2 << InDepth];

	if (TreeArray != nullptr)
	{
		int MaxIndex = 2 << InDepth;
		if (TreeDepth > InDepth)
		{
			MaxIndex = 2 << TreeDepth;
		}

		for (int i = 0; i < MaxIndex; ++i)
		{
			NewTreeArray[i] = TreeArray[i];
		}

		delete[] TreeArray;
	}

	TreeArray = NewTreeArray;
}

template<typename K, typename D, typename Com>
Node<K, D>* BinarySerchTree<K, D, Com>::GetNode(const K& InKey, unsigned int& OutIndex, unsigned int Index)
{
	if (Index >= ArrayCapacity)
	{
		return nullptr;
	}
	if (TreeArray[Index].Key == InKey)
	{
		OutIndex = Index;
		return &TreeArray[Index];
	}
	if (TreeArray[Index].IsFill == false)
	{
		return nullptr;
	}
	if (Comparer(TreeArray[Index].Key, InKey) == true)
	{
		return GetNode(InKey, OutIndex, Index * 2);
	}
	else
	{
		return GetNode(InKey, OutIndex, Index * 2 + 1);
	}
}

template<typename K, typename D, typename Com>
Node<K, D>* BinarySerchTree<K, D, Com>::GetMinNode(unsigned int Index)
{
	if (Index >= ArrayCapacity && Index <= 1)
	{
		return nullptr;
	}
	if (TreeArray[Index].IsFill == false || Index >= ArrayCapacity)
	{
		return &TreeArray[Index / 2];
	}

	return GetMinNode(Index * 2);
}

template<typename K, typename D, typename Com>
Node<K, D>* BinarySerchTree<K, D, Com>::GetMaxNode(unsigned int Index)
{
	if (Index >= ArrayCapacity && Index <= 1)
	{
		return nullptr;
	}
	if (TreeArray[Index].IsFill == false || Index >= ArrayCapacity)
	{
		return &TreeArray[(Index - 1) / 2];
	}

	return GetMinNode(Index * 2 + 1);
}

template<typename K, typename D, typename Com>
void BinarySerchTree<K, D, Com>::CopySubTree(unsigned int OriginIndex, unsigned int TargetIndex)
{
	if (OriginIndex >= ArrayCapacity || TargetIndex >= ArrayCapacity)
	{
		return;
	}
	if (TreeArray[OriginIndex].IsFill == false)
	{
		return;
	}

	TreeArray[TargetIndex] = TreeArray[OriginIndex];

	CopySubTree(OriginIndex * 2, TargetIndex * 2);
	CopySubTree(OriginIndex * 2 + 1, TargetIndex * 2 + 1);
}

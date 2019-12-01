#include <iostream>
#include <string>
#include "BinarySearchTree.h"

int main()
{
	BinarySerchTree<int, std::string> BST;

	BST.InsertNode(2, "����");
	BST.InsertNode(5, "�ź���");
	BST.InsertNode(8, "�䳢");
	BST.InsertNode(7, "ħ����");

	BST.EraseNode(2);

	std::string OutData;
	BST.TryGetData(7, OutData);

	std::cout << OutData << std::endl;

	return 0;
}
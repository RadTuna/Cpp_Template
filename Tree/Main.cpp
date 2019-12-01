#include <iostream>
#include <string>
#include "BinarySearchTree.h"

int main()
{
	BinarySerchTree<int, std::string> BST;

	BST.InsertNode(2, "∞Ì∂Û¥œ");
	BST.InsertNode(5, "∞≈∫œ¿Ã");
	BST.InsertNode(8, "≈‰≥¢");
	BST.InsertNode(7, "ƒß∆“¡ˆ");

	BST.EraseNode(2);

	std::string OutData;
	BST.TryGetData(7, OutData);

	std::cout << OutData << std::endl;

	return 0;
}
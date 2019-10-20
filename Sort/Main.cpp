#include <iostream>
#include <string>
#include "Sort.h"

int main()
{
	int KeyArray[10] = { 5, 7, 4, 6, 2, 1, 3, 9, 8, 0 };
	std::string ValArray[10] = { "�ź�5", "���7", "��4", "�̾�Ĺ6", "�罿2", "���ű�1", "����3", "����9", "���洨8", "�ΰ�0" };

	Sort::RadixSort<int, std::string>(KeyArray, ValArray, 10, 10, 811);

	for (int i = 0; i < 10; ++i)
	{
		std::cout << "Key : " << KeyArray[i] << std::endl;
		std::cout << "Value : " << ValArray[i] << std::endl;
	}

	return 0;
}                            
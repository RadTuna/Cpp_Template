#include "Delegate.h"
#include <iostream>

void PrintText(int num)
{
	std::cout << "Test String!" << num << std::endl;
}

void AltFunction(Del::Delegate<void(int), int>* DelPtr)
{
	DelPtr->Execute(100);
}

int main()
{
	Del::Delegate<void(int), int> MyDelegate;

	MyDelegate.BindDelegate(PrintText);

	AltFunction(&MyDelegate);

	MyDelegate.UnBindDelegate();
}
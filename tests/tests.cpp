// tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Classes/RBTree.h"

void RBTreeTest()
{
	srand((unsigned int)time(nullptr));
	RBTree<int> rb{};
	for (int i = 0; i < 10; i++)
	{
		int num = rand() % 100;
		rb.Insert(num);
		std::cout << num << " ";
	}

	std::cout << std::endl << "----BRTree Test----" << std::endl;
	rb.PrintSelf();
	std::cout << "-------------------" << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	RBTreeTest();

	_getch();
	return 0;
}


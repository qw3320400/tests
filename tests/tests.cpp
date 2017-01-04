// tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Classes/RBTree.h"
#include "Classes/MaxHeap.h"
#include "Classes/Tools.h"
#include "Classes/TMPTest.h"

void RBTreeTest()
{
	srand((unsigned int)time(nullptr));
	RBTree<int> rb{};
	for (int i = 0; i < 10; ++i)
	{
		int num = rand() % 100;
		rb.Insert(num);
		std::cout << num << " ";
	}

	std::cout << std::endl << "----BRTree Test----" << std::endl;
	rb.PrintSelf();
	std::cout << "-------------------" << std::endl;
}

void MaxHeapTest()
{
	srand((unsigned int)time(nullptr));
	Heap<int, HeapType::MinHeap> mh{}; //×îÐ¡¶Ñ
	for (int i = 0; i < 10; ++i)
	{
		int num = rand() % 1000;
		/*mh.Insert(num, true);*/
		mh.Insert(num, false);
		std::cout << num << " ";
	}
	mh.AdjustAll();

	//É¸Ñ¡
	for (int i = 0; i < 100; ++i)
	{
		int num = rand() % 1000;
		mh.Select(num);
		std::cout << num << " ";
	}

	std::cout << std::endl << "----MaxHeap Test----" << std::endl;
	mh.PrintSelf();
	std::cout << (mh.CheckData() ? "true" : "false") << std::endl;
	std::cout << "--------------------" << std::endl;
}

void FastSortTest()
{
	srand((unsigned int)time(nullptr));
	int v[20];
	for (int i = 0; i < 20; ++i)
	{
		int num = rand() % 1000;
		v[i] = num;
		std::cout << num << " ";
	}

	std::cout << std::endl << "----MaxHeap Test----" << std::endl;
	FastSort(v, v + 19);
	std::for_each(v, v + 20, [](const int& p){
		std::cout << p << " ";
	});
	std::cout << std::endl << "--------------------" << std::endl;
}

void TMPTest()
{
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	//RBTreeTest();
	//MaxHeapTest();
	//FastSortTest();
	TMPTest();

	_getch();
	return 0;
}


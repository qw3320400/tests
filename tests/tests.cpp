// tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Classes/RBTree.h"
#include "Classes/MaxHeap.h"

struct oddint
{
	int data;

	oddint()
		:data(0)
	{}

	oddint(int p)
		:data(p)
	{}

	bool operator > (const oddint& p) const throw()
	{
		return data < p.data;
	}

	bool operator == (const oddint& p) const throw()
	{
		return data == p.data;
	}

	bool operator < (const oddint& p) const throw()
	{
		return data > p.data;
	}

	bool operator >= (const oddint& p) const throw()
	{
		return data <= p.data;
	}

	bool operator <= (const oddint& p) const throw()
	{
		return data >= p.data;
	}

	operator int() const throw()
	{
		return data;
	}
};

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
	MaxHeap<oddint> mh{}; //×îÐ¡¶Ñ
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

int _tmain(int argc, _TCHAR* argv[])
{
	//RBTreeTest();
	MaxHeapTest();

	_getch();
	return 0;
}


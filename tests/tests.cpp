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

class wiget { public: ~wiget(){} };
//class scroll : public wiget {};
class button : public wiget {};
class graphicbutton : public button {};
class graphiclabelbutton : public graphicbutton {};

void TMPTest()
{
	//typedef TYPELIST_5(int, char, bool, float, double) T;
	using TL = TYPELIST_5(int, char, bool, float, double);
	std::cout << "LengthOfTypeList : " << LengthOfTypeList<TL>::result << std::endl;

	std::cout << "IndexTypeList : " << typeid(IndexTypeList<TL, 3>::type).name() << std::endl;

	std::cout << "FindInTypeList : " << FindInTypeList<TL, char>::result << std::endl;

	using TL1 = AddToTypeList<TL, short, 4>::type;
	std::cout << "AddToTypeList : " << typeid(TL1).name() << std::endl;

	using TL2 = RemoveFromTypeList<TL1, 3>::type;
	std::cout << "RemoveFromTypeList : " << typeid(TL2).name() << std::endl;

	using TL3 = RemoveAllTFromTypeList<TL2, char>::type;
	std::cout << "RemoveAllTFromTypeList : " << typeid(TL3).name() << std::endl;

	using TL4 = TYPELIST_5(int, char, int, char, double);
	using TL5 = RemoveRepeatFromTypeList<TL4>::type;
	std::cout << "RemoveRepeatFromTypeList : " << typeid(TL5).name() << std::endl;

	using TL6 = ReplaceTypeList<TL4, int, long>::type;
	std::cout << "ReplaceTypeList : " << typeid(TL6).name() << std::endl;

	std::cout << "IS_BASE_OF : " << IS_BASE_OF(wiget, graphicbutton) << std::endl;

	using TL7 = TYPELIST_4(wiget, graphiclabelbutton, button, graphicbutton);
	using TL8 = MostDerivedToTopTypeList<TL7>::type;
	std::cout << "MostDerivedToTopTypeList : " << typeid(TL8).name() << std::endl;
	
	using TL9 = SortTypeList<TL7>::type;
	std::cout << "SortTypeList : " << typeid(TL9).name() << std::endl;
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


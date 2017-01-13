#ifndef _TMPTEST_H
#define _TMPTEST_H

template<typename T>
class policy1_1
{};

template<typename T>
class policy1_2
{};

template<typename T>
class policy2_1
{};

template<typename T>
class policy2_2
{};

template<template<typename> class TP1>
void funimpl()
{
	std::cout << "-----fun1-----\n";
}
template<>
void funimpl<policy1_1>()
{
	std::cout << "-----fun2-----\n";
}

template<typename T,
	template<typename> class P1,
	template<typename> class P2
>
class Test1
	:public P1<T>, public P2<T>
{
private:
	

public:
	inline void fun()
	{
		funimpl<P1>();
	}

private:
	T i;
};

//-----------------

template<bool>
struct STATIC_ASSERT;
template<>
struct STATIC_ASSERT<true>
{};
#define STATIC_ASSERT(expr) STATIC_ASSERT<expr>()

//-----------------

template<int I>
struct Int2Type
{
	enum {value = I};
};

template<typename T>
struct Type2Type
{
	typedef T type;
};

//-----------------

template<bool B, typename T, typename U>
struct SelectType
{
	typedef T type;
};
template<typename T, typename U>
struct SelectType<false, T, U>
{
	typedef U type;
};

//-----------------

template<typename T, typename U>
struct SameType
{
	enum {result = false};
};
template<typename T>
struct SameType<T, T>
{
	enum {result = true};
};

//-----------------

template<typename T, typename U>
class CastTest
{
private:
	struct Big
	{
		char c[2];
	};
	typedef char Small;

	static T MakeT();
	static Small Test(U);
	static Big Test(...);

public:
	enum {
		result = (sizeof(Test(MakeT())) == sizeof(Small))
	};
};
#define IS_BASE_OF(B, D) (!SameType<B, D>::result && !SameType<B, void>::result && CastTest<D*, B*>::result)

//-----------------

template<typename T>
struct PointerToMember
{
	enum {result = false};
};
template<typename T, typename U>
struct PointerToMember<T U::*>
{
	enum {result = true};
};

//-----------------

struct NullType;

struct EmptyType
{};

//-----------------

template<typename T, typename U>
struct TypeList
{
	typedef T Head;
	typedef U Tail;
};

#define TYPELIST_1(T1) TypeList<T1, NullType>
#define TYPELIST_2(T1, T2) TypeList<T1, TYPELIST_1(T2)>
#define	TYPELIST_3(T1, T2, T3) TypeList<T1, TYPELIST_2(T2, T3)>
#define	TYPELIST_4(T1, T2, T3, T4) TypeList<T1, TYPELIST_3(T2, T3, T4)>
#define	TYPELIST_5(T1, T2, T3, T4, T5) TypeList<T1, TYPELIST_4(T2, T3, T4, T5)>

template<typename T>
struct LengthOfTypeList;
template<typename T>
struct LengthOfTypeList<TypeList<T, NullType> >
{
	enum {result =  1};
};
template<typename T, typename U>
struct LengthOfTypeList<TypeList<T, U> >
{
	enum {result = 1 + LengthOfTypeList<U>::result};
};

template<typename T, unsigned int I>
struct IndexTypeList;
template<typename T, typename U>
struct IndexTypeList<TypeList<T, U>, 0>
{
	typedef T type;
};
template<typename T, typename U, unsigned int I>
struct IndexTypeList<TypeList<T, U>, I>
{
	typedef typename IndexTypeList<U, I - 1>::type type;
};

template<typename T, typename U>
struct FindInTypeList;
template<typename T>
struct FindInTypeList<NullType, T>
{
	enum {result = -1};
};
template<typename T, typename U>
struct FindInTypeList<TypeList<T, U>, T>
{
	enum {result = 0};
};
template<typename T, typename U, typename V>
struct FindInTypeList<TypeList<T, U>, V>
{
	//enum { temp = FindInTypeList<U, V>::result };
	enum { result = FindInTypeList<U, V>::result == -1 ? -1 : FindInTypeList<U, V>::result + 1 };
};

template<typename T, typename U, int I>
struct AddToTypeList;
template<typename T, typename U, typename V, int I>
struct AddToTypeList<T, TypeList<U, V>, I>;
template<typename T>
struct AddToTypeList<NullType, T, 0>
{
	typedef TypeList<T, NullType> type;
};
template<typename T, typename U, typename V>
struct AddToTypeList<TypeList<T, U>, V, 0>
{
	typedef TypeList<V, TypeList<T, U> > type;
};
template<typename T, typename U, typename V, int I>
struct AddToTypeList<TypeList<T, U>, V, I>
{
	typedef TypeList<T, typename AddToTypeList<U, V, I - 1>::type> type;
};

template<typename T, int I>
struct RemoveFromTypeList;
template<typename T, typename U>
struct RemoveFromTypeList<TypeList<T, U>, 0>
{
	typedef U type;
};
template<typename T, typename U, int I>
struct RemoveFromTypeList<TypeList<T, U>, I>
{
	typedef TypeList<T, typename RemoveFromTypeList<U, I - 1>::type> type;
};

template<typename T, typename U>
struct RemoveAllTFromTypeList;
template<typename T>
struct RemoveAllTFromTypeList<NullType, T>
{
	typedef NullType type;
};
template<typename T, typename U>
struct RemoveAllTFromTypeList<TypeList<T, U>, T>
{
	//RemoveFirstT : typedef U type;
	typedef typename RemoveAllTFromTypeList<U, T>::type type;
};
template<typename T, typename U, typename V>
struct RemoveAllTFromTypeList<TypeList<T, U>, V>
{
	typedef TypeList<T, typename RemoveAllTFromTypeList<U, V>::type> type;
};

template<typename T>
struct RemoveRepeatFromTypeList;
template<>
struct RemoveRepeatFromTypeList<NullType>
{
	typedef NullType type;
};
template<typename T, typename U>
struct RemoveRepeatFromTypeList<TypeList<T, U> >
{
	typedef TypeList<T, 
		typename RemoveRepeatFromTypeList<
			typename RemoveAllTFromTypeList<U, T>::type
		>::type
	> type;
};

template<typename T, typename U, typename V>
struct ReplaceTypeList;
template<typename T, typename U>
struct ReplaceTypeList<NullType, T, U>
{
	typedef NullType type;
};
template<typename T, typename U, typename V>
struct ReplaceTypeList<TypeList<T, U>, T, V>
{
	//ReplaceFirstT : typedef TypeList<V, U> type;
	typedef TypeList<V, typename ReplaceTypeList<U, T, V>::type> type;
};
template<typename T, typename U, typename V, typename W>
struct ReplaceTypeList<TypeList<T, U>, V, W>
{
	typedef TypeList<T, typename ReplaceTypeList<U, V, W>::type> type;
};

template<typename T>
struct CompareElementTypeList;
template<typename T, typename U, typename V>
struct CompareElementTypeList<TypeList<T, TypeList<U, V> > >
{
	typedef typename SelectType<IS_BASE_OF(T, U), TypeList<U, TypeList<T, V> >, TypeList<T, TypeList<U, V> > >::type type;
};

template<typename T>
struct MostDerivedToTopTypeList;
template<typename T>
struct MostDerivedToTopTypeList<TypeList<T, NullType> >
{
	typedef TypeList<T, NullType> temp;
	typedef TypeList<T, NullType> type;
};
template<typename T, typename U>
struct MostDerivedToTopTypeList<TypeList<T, U> >
{
	typedef typename MostDerivedToTopTypeList<U>::type temp;
	typedef typename CompareElementTypeList<TypeList<T, temp> >::type type;
};

template<typename T>
struct SortTypeList;
template<typename T>
struct SortTypeList<TypeList<T, NullType> >
{
	typedef TypeList<T, NullType> type;
};
template<typename T, typename U>
struct SortTypeList<TypeList<T, U> >
{
	typedef typename MostDerivedToTopTypeList<TypeList<T, U> >::type temp;
	typedef typename SortTypeList<typename temp::Tail>::type tail;
	typedef typename temp::Head head;
	typedef TypeList<head, tail> type;
};

//-----------------

template<typename T>
struct Unit
{
	T value;
};

template<typename T, template<typename> class U>
struct UnitList
	:public U<T>
{};
template<template<typename> class T>
struct UnitList<NullType, T>
{};
template<typename T, typename U, template<typename> class V>
struct UnitList<TypeList<T, U>, V>
	:public UnitList<T, V>, public UnitList<U, V>
{};

//-----------------

template<typename T, typename U>
struct LineUnit : public U
{
	T value;
};

template<typename T, template<typename, typename> class U, typename ROOT = EmptyType>
struct LineUnitList;
template<template<typename, typename> class T, typename ROOT>
struct LineUnitList<NullType, T, ROOT>
	: public ROOT
{};
template<typename T, typename U, template<typename, typename> class V, typename ROOT>
struct LineUnitList<TypeList<T, U>, V, ROOT>
	: public V<T, LineUnitList<U, V, ROOT> >
{};

//-----------------

template<typename T, typename = typename std::enable_if<std::is_same<int, T>::value>::type>
void funtest(int)
{
	std::cout << "funtest111111" << std::endl;
}

#endif
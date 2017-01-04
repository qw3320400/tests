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
#define IS_BASE_OF(B, D) CastTest<B*, D*>::result

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

// template<typename ...T>
// struct TypeList
// {
// 	enum {
// 		T = 0
// 	};
// };

#endif
#pragma once
#include "Algorithm.h"
#include <type_traits>

template<class Func, class Ret, class... Args>
class DynamicAlgorithm : public Algorithm<Ret, Args...>
{
public:
	DynamicAlgorithm(Func);
	Ret run(Args&...);
private:
	Func fn;
};

template<class Func, class Ret, class ...Args>
inline DynamicAlgorithm<Func, Ret, Args...>::DynamicAlgorithm(Func fn)
	: fn(fn)
{
}

template<class Func, class Ret, class ...Args>
inline Ret DynamicAlgorithm<Func, Ret, Args...>::run(Args&... args)
{
	return fn(args...);
}
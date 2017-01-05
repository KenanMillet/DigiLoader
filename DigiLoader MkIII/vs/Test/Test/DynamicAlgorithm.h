#ifndef _DYNAMIC_ALGORITHM_H
#define _DYNAMIC_ALGORITHM_H

#include "Algorithm.h"
#include <functional>

#include "util.h"

template <class RetType, class ...Args>
class DynamicAlgorithm final : public Algorithm<RetType, Args...>
{
public:
	DynamicAlgorithm(const std::function<RetType(Args...)>&, const std::initializer_list<const char* const>& = {});
	DynamicAlgorithm(const DynamicAlgorithm<RetType, Args...>&);
	DynamicAlgorithm<RetType, Args...>& operator=(const DynamicAlgorithm<RetType, Args...>&);


protected:
	virtual void exec();
private:
	std::function<RetType(Args...)> func;
};

template <class RetType, class ...Args>
DynamicAlgorithm<RetType, Args...>::DynamicAlgorithm(const std::function<RetType(Args...)>& function, const std::initializer_list<const char* const>& reqs)
	: Algorithm<RetType, Args...>(reqs), func(function)
{

}

template <class RetType, class ...Args>
DynamicAlgorithm<RetType, Args...>::DynamicAlgorithm(const DynamicAlgorithm<RetType, Args...>& src)
	: Algorithm<RetType, Args...>(src), func(src.func)
{

}

template <class RetType, class ...Args>
DynamicAlgorithm<RetType, Args...>& DynamicAlgorithm<RetType, Args...>::operator=(const DynamicAlgorithm<RetType, Args...>& src)
{
	Algorithm<RetType, Args...>::operator=(other);
	func = src.func;
	return *this;
}

template <class RetType, class ...Args>
void DynamicAlgorithm<RetType, Args...>::exec()
{
	std::tuple<Args...> params;
	Util::Tuple::from_vArray(getArgs(), params);
	output(Util::Tuple::apply(func, params));
}

#endif
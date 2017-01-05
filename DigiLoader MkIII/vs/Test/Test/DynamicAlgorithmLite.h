#ifndef _DYNAMIC_ALGORITHM_LITE_H
#define _DYNAMIC_ALGORITHM_LITE_H

#include "AlgorithmLite.h"
#include <functional>

#include "UtilLite.h"

template <class RetType, class ...Args>
class DynamicAlgorithmLite final : public AlgorithmLite<RetType, Args...>
{
public:
	DynamicAlgorithmLite(const std::function<RetType(Args...)>&, const std::initializer_list<const char* const>& = {});
	DynamicAlgorithmLite(const DynamicAlgorithmLite<RetType, Args...>&);
	DynamicAlgorithmLite<RetType, Args...>& operator=(const DynamicAlgorithmLite<RetType, Args...>&);


protected:
	virtual void exec();
private:
	std::function<RetType(Args...)> func;
};

template <class RetType, class ...Args>
DynamicAlgorithmLite<RetType, Args...>::DynamicAlgorithmLite(const std::function<RetType(Args...)>& function, const std::initializer_list<const char* const>& reqs)
	: AlgorithmLite<RetType, Args...>(reqs), func(function)
{

}

template <class RetType, class ...Args>
DynamicAlgorithmLite<RetType, Args...>::DynamicAlgorithmLite(const DynamicAlgorithmLite<RetType, Args...>& src)
	: AlgorithmLite<RetType, Args...>(src), func(src.func)
{

}

template <class RetType, class ...Args>
DynamicAlgorithmLite<RetType, Args...>& DynamicAlgorithmLite<RetType, Args...>::operator=(const DynamicAlgorithmLite<RetType, Args...>& src)
{
	AlgorithmLite<RetType, Args...>::operator=(other);
	func = src.func;
	return *this;
}

template <class RetType, class ...Args>
void DynamicAlgorithmLite<RetType, Args...>::exec()
{
	tuple<Args...> params;
	UtilLite::Tuple::from_vArray(getArgs(), params);
	output(UtilLite::Tuple::apply(func, params));
}

#endif
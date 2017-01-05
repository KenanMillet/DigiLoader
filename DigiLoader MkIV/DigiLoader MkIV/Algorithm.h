#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include "AlgorithmBase.h"

template<typename RetType, class ...Args>
class Algorithm : public AlgorithmBase
{
public:
	typedef RetType returnType;
	typedef std::tuple<Args...> argPackType;
	template <int N>
	auto argType();

public:

	Algorithm(const std::initializer_list<const char* const>& = {});
	Algorithm(const std::initializer_list<const char* const>&, const std::map<const char* const, AlgorithmBase*>&);

	operator RetType&();
	operator RetType() const;

	Algorithm<RetType, Args...>& operator()(Args...);
	virtual Algorithm<RetType, Args...>& operator()(const std::initializer_list<void*>&);
	virtual Algorithm<RetType, Args...>& operator()(const std::vector<void*>&);

	virtual Algorithm<RetType, Args...>& run(const char* const);

protected:

private:

};



template <typename RetType, class ...Args>
template <int N>
auto Algorithm<RetType, Args...>::argType()
{
	return std::tuple_element<N, std::tuple<Args...>>::type;
}



template<typename RetType, class ...Args>
Algorithm<RetType, Args...>::Algorithm(const std::initializer_list<const char* const>& reqs)
	: AlgorithmBase(sizeof...(Args), reqs)
{

}

template<typename RetType, class ...Args>
Algorithm<RetType, Args...>::Algorithm(const std::initializer_list<const char* const>& reqs, const std::map<const char* const, AlgorithmBase*>& set)
	: AlgorithmBase(sizeof...(Args), reqs, set)
{

}

template<typename RetType, class ...Args>
Algorithm<RetType, Args...>& Algorithm<RetType, Args...>::run(const char* const name)
{
	return dynamic_cast<Algorithm<RetType, Args...>&>(AlgorithmBase::run(name));
}

template<typename RetType, class ...Args>
Algorithm<RetType, Args...>::operator RetType&()
{
	return result<RetType>();
}
template<typename RetType, class ...Args>
Algorithm<RetType, Args...>::operator RetType() const
{
	return result<RetType>();
}

template<typename RetType, class ...Args>
Algorithm<RetType, Args...>& Algorithm<RetType, Args...>::operator()(Args... args)
{
	return dynamic_cast<Algorithm<RetType, Args...>&>(AlgorithmBase::operator()<Args...>(args...));
}

template<typename RetType, class ...Args>
Algorithm<RetType, Args...>& Algorithm<RetType, Args...>::operator()(const std::initializer_list<void*>& args)
{
	return dynamic_cast<Algorithm<RetType, Args...>&>(AlgorithmBase::operator()(args));
}

template<typename RetType, class ...Args>
Algorithm<RetType, Args...>& Algorithm<RetType, Args...>::operator()(const std::vector<void*>& args)
{
	return dynamic_cast<Algorithm<RetType, Args...>&>(AlgorithmBase::operator()(args));
}

#endif
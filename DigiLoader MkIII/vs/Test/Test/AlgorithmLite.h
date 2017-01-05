#ifndef _ALGORITHM_LITE_H
#define _ALGORITHM_LITE_H

#include "AlgorithmBaseLite.h"

template<typename RetType, class ...Args>
class AlgorithmLite : public AlgorithmBaseLite
{
public:
	typedef RetType returnType;
	typedef std::tuple<Args...> argPackType;
	template <int N>
	auto argType();

public:

	AlgorithmLite(const std::initializer_list<const char* const>& = {});
	AlgorithmLite(const std::initializer_list<const char* const>&, const std::map<const char* const, AlgorithmBaseLite*>&);

	operator RetType&();
	operator RetType() const;

	AlgorithmLite<RetType, Args...>& operator()(Args...);
	virtual AlgorithmLite<RetType, Args...>& operator()(const std::initializer_list<void*>&);
	virtual AlgorithmLite<RetType, Args...>& operator()(const std::vector<void*>&);

	virtual AlgorithmLite<RetType, Args...>& run(const char* const);

protected:

private:

};



template <typename RetType, class ...Args>
template <int N>
auto AlgorithmLite<RetType, Args...>::argType()
{
	return std::tuple_element<N, std::tuple<Args...>>::type;
}



template<typename RetType, class ...Args>
AlgorithmLite<RetType, Args...>::AlgorithmLite(const std::initializer_list<const char* const>& reqs)
	: AlgorithmBaseLite(sizeof...(Args), reqs)
{

}

template<typename RetType, class ...Args>
AlgorithmLite<RetType, Args...>::AlgorithmLite(const std::initializer_list<const char* const>& reqs, const std::map<const char* const, AlgorithmBaseLite*>& set)
	: AlgorithmBaseLite(sizeof...(Args), reqs, set)
{

}

template<typename RetType, class ...Args>
AlgorithmLite<RetType, Args...>& AlgorithmLite<RetType, Args...>::run(const char* const name)
{
	return dynamic_cast<AlgorithmLite<RetType, Args...>&>(AlgorithmBaseLite::run(name));
}

template<typename RetType, class ...Args>
AlgorithmLite<RetType, Args...>::operator RetType&()
{
	return result<RetType>();
}
template<typename RetType, class ...Args>
AlgorithmLite<RetType, Args...>::operator RetType() const
{
	return result<RetType>();
}

template<typename RetType, class ...Args>
AlgorithmLite<RetType, Args...>& AlgorithmLite<RetType, Args...>::operator()(Args... args)
{
	return dynamic_cast<AlgorithmLite<RetType, Args...>&>(AlgorithmBaseLite::operator()<Args...>(args...));
}

template<typename RetType, class ...Args>
AlgorithmLite<RetType, Args...>& AlgorithmLite<RetType, Args...>::operator()(const std::initializer_list<void*>& args)
{
	return dynamic_cast<AlgorithmLite<RetType, Args...>&>(AlgorithmBaseLite::operator()(args));
}

template<typename RetType, class ...Args>
AlgorithmLite<RetType, Args...>& AlgorithmLite<RetType, Args...>::operator()(const std::vector<void*>& args)
{
	return dynamic_cast<AlgorithmLite<RetType, Args...>&>(AlgorithmBaseLite::operator()(args));
}

#endif
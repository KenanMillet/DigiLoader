#pragma once
#include <string>
#include <functional>
#include <initializer_list>
#include <map>

class Ialgorithm
{
public:
	virtual ~Ialgorithm();

	virtual operator bool();
	virtual bool isGood() = 0;

	//Junk operator meant to be hidden. Do not use.
	virtual void operator()();

private:
	const std::string desc;
	const std::map<std::string, Ialgorithm*> reqs;
};

template<class RetType = void, class ...Args>
class Algorithm : public Ialgorithm
{
public:
	//Move/Default constructor
	Algorithm(const std::string&& = "", const std::function<RetType(Args...)>&& = std::function<RetType(Args...)>()/*RetType(*const func)(Args...) = nullptr*/, std::initializer_list<std::string>&& = std::initializer_list<std::string>());
	//Initialization constructor
	Algorithm(const std::string&, const std::function<RetType(Args...)>&/*RetType(*const func)(Args...)*/, std::initializer_list<std::string>&);

	//Functional Operator: runs the function of the algorithm
	RetType operator()(Args...);

	//Run another algorithm in reqs
	//template<class Returned = void, class ...Params>
	//Returned run(const std::string&, Params...);
	auto run(const std::string&, )
private:
	const std::function<RetType(Args...)> func;/*RetType(*const func)(Args...)*/
};


inline Ialgorithm::~Ialgorithm()
{

}

inline Ialgorithm::operator bool()
{
	return isGood();
}

//Junk operator meant to be hidden. Do not use.
inline void Ialgorithm::operator()()
{
}


template<class RetType = void, class ...Args>
inline Algorithm<RetType, Args...>::Algorithm(const std::string&& description, const std::function<RetType(Args...)>&& function/*RetType(*const function)(Args...)*/, std::initializer_list<std::string>&& requirements)
	: desc(description), func(function), reqs()
{
	for(const std::string* i = requirements.begin(); i != requirements.end(); ++i) reqs.insert(std::pair<std::string, Algorithm<RetType, Args...>>(*i, nullptr));
}

template<class RetType = void, class ...Args>
inline Algorithm<RetType, Args...>::Algorithm(const std::string& description, const std::function<RetType(Args...)>& function/*RetType(*const function)(Args...)*/, std::initializer_list<std::string>& requirements)
	: desc(description), func(function), reqs()
{
	for(const std::string* i = requirements.begin(); i != requirements.end(); ++i) reqs.insert(std::pair<std::string, Algorithm<RetType, Args...>>(*i, nullptr));
}

template<class RetType = void, class ...Args>
inline RetType Algorithm<RetType, Args...>::operator()(Args... params)
{
	return func(params);
}

//template<class RetType, class ...Args>
//template<class Returned, class ...Params>
//inline Returned Algorithm<RetType, ...Args>::run(const std::string& desc, Params... params)
//{
//	if(desc == "") return func(params);
//	return (Algorithm<Returned, ...Params>*)(reqs[desc])->run(params);
//}
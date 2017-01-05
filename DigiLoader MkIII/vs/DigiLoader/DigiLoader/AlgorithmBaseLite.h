#ifndef _ALGORITHM_BASE_LITE_H
#define _ALGORITHM_BASE_LITE_H

#include <initializer_list>
#include <map>
#include <vector>

#include "UtilLite.h"

class AlgorithmBaseLite
{
public:
	AlgorithmBaseLite(const size_t, const std::initializer_list<const char* const>& = {});
	AlgorithmBaseLite(const size_t, const std::initializer_list<const char* const>&, const std::map<const char* const, AlgorithmBaseLite*>&);
	virtual ~AlgorithmBaseLite();

	template<class... Args>
	AlgorithmBaseLite& operator()(Args...);
	virtual AlgorithmBaseLite& operator()(const std::initializer_list<void*>&);
	virtual AlgorithmBaseLite& operator()(const std::vector<void*>&);

	virtual AlgorithmBaseLite& run(const char* const);
	AlgorithmBaseLite& operator[](const char* const);

	template <class Type>
	Type& result();

	bool setReq(const char* const, AlgorithmBaseLite* const);

	size_t numArgs() const;

protected:
	virtual void exec() = 0;

	void setReq(const char* const);

	template <class Type>
	Type& arg(const size_t) const;
	std::vector<void*>& getArgs();

	template<class Type>
	void output(Type&& value);

private:
	AlgorithmBaseLite(const AlgorithmBaseLite&) = default;
	AlgorithmBaseLite& operator=(const AlgorithmBaseLite&) = default;

	std::vector<void*> args;

	void* returnedObject;

	std::map<const char* const, AlgorithmBaseLite*> reqs;
};


template<class ...Args>
AlgorithmBaseLite& AlgorithmBaseLite::operator()(Args... params)
{
	UtilLite::Tuple::to_vArray(std::tuple<Args...>(params...), args);
	return this->operator()(args);
}


template <class Type>
Type& AlgorithmBaseLite::result()
{
	return *((Type*) (returnedObject));
}

template <class Type>
Type& AlgorithmBaseLite::arg(const size_t index) const
{
	return *((Type*) (args[index]));
}

template<class Type>
void AlgorithmBaseLite::output(Type&& value)
{
	if(returnedObject == nullptr)
	{
		returnedObject = new Type(std::forward<Type>(value));
		return;
	}
	result<Type>() = value;
}

#endif
#ifndef _ALGORITHM_BASE_H
#define _ALGORITHM_BASE_H

#include <initializer_list>
#include <map>
#include <vector>

class AlgorithmBase
{
public:
	AlgorithmBase(const size_t, const std::initializer_list<const char* const>& = {});
	AlgorithmBase(const size_t, const std::initializer_list<const char* const>&, const std::map<const char* const, AlgorithmBase*>&);
	virtual ~AlgorithmBase();

	template<class... Args>
	AlgorithmBase& operator()(Args...);
	virtual AlgorithmBase& operator()(const std::initializer_list<void*>&);
	virtual AlgorithmBase& operator()(const std::vector<void*>&);

	virtual AlgorithmBase& run(const char* const);
	AlgorithmBase& operator[](const char* const);

	template <class Type>
	Type& result();

	bool setReq(const char* const, AlgorithmBase* const);

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
	AlgorithmBase(const AlgorithmBase&) = default;
	AlgorithmBase& operator=(const AlgorithmBase&) = default;

	std::vector<void*> args;

	void* returnedObject;

	std::map<const char* const, AlgorithmBase*> reqs;
};


template<class ...Args>
AlgorithmBase& AlgorithmBase::operator()(Args... params)
{
	Util::Tuple::to_vArray(std::tuple<Args...>(params...), args);
	return this->operator()(args);
}


template <class Type>
Type& AlgorithmBase::result()
{
	return *((Type*) (returnedObject));
}

template <class Type>
Type& AlgorithmBase::arg(const size_t index) const
{
	return *((Type*) (args[index]));
}

template<class Type>
void AlgorithmBase::output(Type&& value)
{
	if(returnedObject == nullptr)
	{
		returnedObject = new Type(std::forward<Type>(value));
		return;
	}
	result<Type>() = value;
}

#endif
#pragma once
#include "BaseAlgorithm.h"

template<class Ret, class... Args>
class Algorithm : public BaseAlgorithm
{
public:
	Algorithm();

	virtual Ret run(Args&...) = 0;
	Ret operator()(Args&...);

	Algorithm<Ret, Args...>& invoke(void**, size_t) final;
	Ret result() const;
	operator Ret() const;
private:
	Ret* retValue;
};

template<class Ret>
class Algorithm<Ret> : public BaseAlgorithm
{
public:
	Algorithm();

	virtual Ret run() = 0;
	Ret operator()();

	Algorithm<Ret>& invoke(void**, size_t) final;
	Ret result() const;
	operator Ret() const;
private:
	Ret* retValue;
};

template<class Ret, class ...Args>
inline Algorithm<Ret, Args...>::Algorithm()
	: retValue(nullptr)
{
}

template<class Ret>
inline Algorithm<Ret>::Algorithm()
	: retValue(nullptr)
{
}

template<class Ret, class... Args>
inline Ret Algorithm<Ret, Args...>::operator()(Args&... args)
{
	return run(args...);
}

template<class Ret>
inline Ret Algorithm<Ret>::operator()()
{
	return run();
}

template<class Ret, class... Args>
inline Algorithm<Ret, Args...>& Algorithm<Ret, Args...>::invoke(void** args, size_t size)
{
	auto next = [](void**& a) {return *a++; };
	delete retValue;
	retValue = new Ret(run(*((Args*)next(args))...) );
	return *this;
}

template<class Ret>
inline Algorithm<Ret>& Algorithm<Ret>::invoke(void** args, size_t size)
{
	delete retValue;
	retValue = new Ret(run());
	return *this;
}

template<class Ret, class... Args>
inline Ret Algorithm<Ret, Args...>::result() const
{
	return *retValue;
}

template<class Ret>
inline Ret Algorithm<Ret>::result() const
{
	return *retValue;
}

template<class Ret, class... Args>
inline Algorithm<Ret, Args...>::operator Ret() const
{
	return result();
}

template<class Ret>
inline Algorithm<Ret>::operator Ret() const
{
	return result();
}
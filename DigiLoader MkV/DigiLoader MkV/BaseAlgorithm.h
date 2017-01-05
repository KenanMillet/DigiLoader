#pragma once

class BaseAlgorithm
{
public:
	template<class A, class... Args> auto invoke(A&, Args&...);
	auto invoke();
	virtual BaseAlgorithm& invoke(void**, size_t) = 0;
private:
	void* result() const;
};

template<class A, class... Args>
inline auto BaseAlgorithm::invoke(A& arg, Args&... args)
{
	auto convert = [](auto& a) {return ((void*) (&a)); };
	void* varargs[] = { convert(arg), convert(args)... };
	return invoke(varargs, 1 + sizeof...(args)).result();
}

inline auto BaseAlgorithm::invoke()
{
	return invoke(nullptr, 0).result();
}

inline void* BaseAlgorithm::result() const
{
	return nullptr;
}

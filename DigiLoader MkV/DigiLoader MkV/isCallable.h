#pragma once

template <class T>
class isCallable
{
private:
    using yes = char[2];
    using  no = char[1];

	struct Pitfall { void operator()(); };
    struct Trigger : T, Pitfall {};

	template <class Subject> static yes& test(Subject*);
	template <class Subject> static no& test(decltype(&Subject::operator())*);

public:
	typedef bool value_type;
    static constexpr bool value = sizeof(test<Trigger>(nullptr)) == sizeof(yes);
	constexpr operator bool() const noexcept;
	constexpr bool operator()() const noexcept;
};

template<class Ret, class... Args>
class isCallable<Ret(*)(Args...)>
{
public:
	typedef bool value_type;
	static constexpr bool value = true;
	constexpr operator bool() const noexcept { return true; }
	constexpr bool operator()() const noexcept { return true; }
};

template<class C, class Ret, class... Args>
class isCallable<Ret(C::*)(Args...)>
{
public:
	typedef bool value_type;
	static constexpr bool value = true;
	constexpr operator bool() const noexcept { return true; }
	constexpr bool operator()() const noexcept { return true; }
};

template<class C, class Ret, class... Args>
class isCallable<Ret(C::*)(Args...) const>
{
public:
	typedef bool value_type;
	static constexpr bool value = true;
	constexpr operator bool() const noexcept { return true; }
	constexpr bool operator()() const noexcept { return true; }
};

template<class T>
inline constexpr isCallable<T>::operator bool() const noexcept
{
	return value;
}

template<class T>
inline constexpr bool isCallable<T>::operator()() const noexcept
{
	return value;
}



template <class T>
class isValidCall
{
private:
	using yes = char[2];
	using  no = char[1];

	struct Pitfall { void operator()(); };
	struct Trigger : T, Pitfall {};

	template <class Subject> static yes& test(Subject*);
	template <class Subject> static no& test(decltype(&Subject::operator())*);

public:
	typedef bool value_type;
	static constexpr bool value = sizeof(test<Trigger>(nullptr)) == sizeof(yes);
	constexpr operator bool() const noexcept;
	constexpr bool operator()() const noexcept;
};

template<class Ret, class... Args>
class isValidCall<Ret(*)(Args...)>
{
public:
	typedef bool value_type;
	static constexpr bool value = true;
	constexpr operator bool() const noexcept { return true; }
	constexpr bool operator()() const noexcept { return true; }
};

template<class C, class Ret, class... Args>
class isValidCall<Ret(C::*)(Args...)>
{
public:
	typedef bool value_type;
	static constexpr bool value = true;
	constexpr operator bool() const noexcept { return true; }
	constexpr bool operator()() const noexcept { return true; }
};

template<class C, class Ret, class... Args>
class isValidCall<Ret(C::*)(Args...) const>
{
public:
	typedef bool value_type;
	static constexpr bool value = true;
	constexpr operator bool() const noexcept { return true; }
	constexpr bool operator()() const noexcept { return true; }
};

template<class T>
inline constexpr isValidCall<T>::operator bool() const noexcept
{
	return value;
}

template<class T>
inline constexpr bool isValidCall<T>::operator()() const noexcept
{
	return value;
}
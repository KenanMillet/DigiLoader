#pragma once

//Main Template Version
template<class Ret = void, class... Args>
class Algorithm
{
public:
	Algorithm() = default;
	virtual Ret operator()(Args...) = 0;
	virtual operator bool() const;
	virtual ~Algorithm() = default;
};

//Specialization for Function Pointers
template<class Ret, class... Args>
class Algorithm<Ret(*)(Args...)> : public Algorithm<Ret, Args...>
{
public:
	typedef Ret(*CallType)(Args...);
	Algorithm(CallType = doNothing);

	Algorithm(const Algorithm<CallType>&) = default;
	Algorithm(Algorithm<CallType>&&) = default;
	Algorithm<Ret(*)(Args...)>& operator=(const Algorithm<CallType>&) = default;
	Algorithm<Ret(*)(Args...)>& operator=(Algorithm<CallType>&&) = default;

	Algorithm<Ret(*)(Args...)>& operator=(CallType);

	virtual ~Algorithm() = default;

	Ret operator()(Args...);
	operator bool() const;
private:
	Ret(*fn)(Args...);
	static Ret(*doNothing)(Args...);
};
//Specialization for Function Pointers returning void
template<class... Args>
class Algorithm<void(*)(Args...)> : public Algorithm<void, Args...>
{
public:
	typedef void(*CallType)(Args...);
	Algorithm(CallType = doNothing);

	Algorithm(const Algorithm<CallType>&) = default;
	Algorithm(Algorithm<CallType>&&) = default;
	Algorithm<void(*)(Args...)>& operator=(const Algorithm<CallType>&) = default;
	Algorithm<void(*)(Args...)>& operator=(Algorithm<CallType>&&) = default;

	Algorithm<void(*)(Args...)>& operator=(CallType);

	virtual ~Algorithm() = default;

	void operator()(Args...);
	operator bool() const;
private:
	void(*fn)(Args...);
	static void(*doNothing)(Args...);
};

//Specialization for Lambda Functions
template<class Ret, class... Args>
class Algorithm<Ret(Args...)> : public Algorithm<Ret, Args...>
{
public:
	typedef Ret(*CallType)(Args...);
	Algorithm();
	template<class Lambda> Algorithm(const Lambda& lambda);
	
	Algorithm(const Algorithm<Ret(Args...)>&);
	Algorithm(Algorithm<Ret(Args...)>&&);
	Algorithm<Ret(Args...)>& operator=(const Algorithm<Ret(Args...)>&);
	Algorithm<Ret(Args...)>& operator=(Algorithm<Ret(Args...)>&&);
	
	template<class Lambda> Algorithm<Ret(Args...)>& operator=(const Lambda& lambda);

	virtual ~Algorithm();

	Ret operator()(Args...);
	operator bool() const;
private:
	void* lambda;
	void(*delLambda)(void*);
	void*(*copyLambda)(void*);
	Ret(*applyLambda)(void*, Args...);
	bool is_good;
};
//Specialization for Lambda Functions returning void
template<class... Args>
class Algorithm<void(Args...)> : public Algorithm<void, Args...>
{
public:
	typedef void(*CallType)(Args...);
	Algorithm();
	template<class Lambda> Algorithm(const Lambda& lambda);
	
	Algorithm(const Algorithm<void(Args...)>&);
	Algorithm(Algorithm<void(Args...)>&&);
	Algorithm<void(Args...)>& operator=(const Algorithm<void(Args...)>&);
	Algorithm<void(Args...)>& operator=(Algorithm<void(Args...)>&&);

	template<class Lambda> Algorithm<void(Args...)>& operator=(const Lambda& lambda);

	virtual ~Algorithm();
	
	void operator()(Args...);
	operator bool() const;
private:
	void* lambda;
	void(*delLambda)(void*);
	void*(*copyLambda)(void*);
	void(*applyLambda)(void*, Args...);
	bool is_good;
};



//////////////////////
//Member Definitions//
//////////////////////

//Main Template Version
template<class Ret, class... Args>
inline Algorithm<Ret, Args...>::operator bool() const
{
	return true;
}



//Specialization for Function Pointers
template<class Ret, class... Args>
inline Algorithm<Ret(*)(Args...)>::Algorithm(CallType fn)
	: fn(fn)
{
}

template<class Ret, class... Args>
inline Algorithm<Ret(*)(Args...)>& Algorithm<Ret(*)(Args...)>::operator=(CallType fn)
{
	this->fn = fn;
}

template<class Ret, class... Args>
inline Ret Algorithm<Ret(*)(Args...)>::operator()(Args... args)
{
	return fn(args...);
}

template<class Ret, class... Args>
inline Algorithm<Ret(*)(Args...)>::operator bool() const
{
	return (fn == doNothing);
}

template<class Ret, class... Args>
Ret(*Algorithm<Ret(*)(Args...)>::doNothing)(Args...) = [](Args...) { return Ret(); };
//Specialization for Function Pointers returning void
template<class... Args>
inline Algorithm<void(*)(Args...)>::Algorithm(CallType fn)
	: fn(fn)
{
}

template<class... Args>
inline Algorithm<void(*)(Args...)>& Algorithm<void(*)(Args...)>::operator=(CallType fn)
{
	this->fn = fn;
}

template<class... Args>
inline void Algorithm<void(*)(Args...)>::operator()(Args... args)
{
	fn(args...);
}

template<class... Args>
inline Algorithm<void(*)(Args...)>::operator bool() const
{
	return (fn == doNothing);
}

template<class... Args>
void(*Algorithm<void(*)(Args...)>::doNothing)(Args...) = [](Args...) {};



//Specialization for Lambda Functions
template<class Ret, class... Args>
inline Algorithm<Ret(Args...)>::Algorithm()
	: is_good(false)
{
	auto placeholder = [](Args...) -> Ret { return Ret(); };
	typedef decltype(placeholder) PL;
	lambda = new PL(placeholder);
	delLambda = [](void* l) { delete ((PL*) l); };
	copyLambda = [](void* l) -> void* { new PL(*((PL*) l)); };
	applyLambda = [](void* l, Args... args) -> Ret { return ((PL*) l)->operator()(args...); };
}

template<class Ret, class... Args>
template<class Lambda>
inline Algorithm<Ret(Args...)>::Algorithm(const Lambda& lambda)
	: is_good(true)
{
	this->lambda = new Lambda(lambda);
	delLambda = [](void* l) { delete ((Lambda*) l); };
	copyLambda = [](void* l) -> void* { return new Lambda(*((Lambda*) l)); };
	applyLambda = [](void* l, Args... args) -> Ret { return ((Lambda*) l)->operator()(args...); };
}

template<class Ret, class... Args>
inline Algorithm<Ret(Args...)>::Algorithm(const Algorithm<Ret(Args...)>& obj)
	: lambda(obj.copyLambda(obj.lambda)),
	delLambda(obj.delLambda),
	copyLambda(obj.copyLambda),
	applyLambda(obj.applyLambda),
	is_good(obj.is_good)
{
}

template<class Ret, class... Args>
inline Algorithm<Ret(Args...)>::Algorithm(Algorithm<Ret(Args...)>&& tmp)
	: lambda(tmp.lambda),
	delLambda(tmp.delLambda),
	copyLambda(tmp.copyLambda),
	applyLambda(tmp.applyLambda),
	is_good(tmp.is_good)
{
	tmp.delLambda = [](void*) {};
}

template<class Ret, class... Args>
inline Algorithm<Ret(Args...)>& Algorithm<Ret(Args...)>::operator=(const Algorithm<Ret(Args...)>& obj)
{
	delLambda(lambda);
	lambda = obj.copyLambda(obj.lambda);
	delLambda = obj.delLambda;
	copyLambda = obj.copyLambda;
	applyLambda = obj.applyLambda;
	is_good = obj.is_good;
	return *this;
}

template<class Ret, class... Args>
inline Algorithm<Ret(Args...)>& Algorithm<Ret(Args...)>::operator=(Algorithm<Ret(Args...)>&& tmp)
{
	void* oldLambda = lambda;
	void(*oldDel)(void*) = delLambda;
	lambda = tmp.lambda;
	delLambda = tmp.delLambda;
	tmp.lambda = oldLambda;
	tmp.delLambda = oldDel;
	copyLambda = tmp.copyLambda;
	applyLambda = tmp.applyLambda;
	is_good = tmp.is_good;
	return *this;
}

template<class Ret, class... Args>
template<class Lambda>
inline Algorithm<Ret(Args...)>& Algorithm<Ret(Args...)>::operator=(const Lambda& lambda)
{
	delLambda(this->lambda);
	this->lambda = new Lambda(lambda);
	delLambda = [](void* l) { delete ((Lambda*) l); };
	copyLambda = [](void* l) -> void* { new Lambda(*((Lambda*) l)); };
	applyLambda = [](void* l, Args... args) -> Ret { return ((Lambda*) l)->operator()(args...); };
	is_good = true;
	return *this;
}

template<class Ret, class... Args>
inline Algorithm<Ret(Args...)>::~Algorithm()
{
	delLambda(lambda);
}

template<class Ret, class... Args>
inline Ret Algorithm<Ret(Args...)>::operator()(Args... args)
{
	return applyLambda(lambda, args...);
}

template<class Ret, class... Args>
inline Algorithm<Ret(Args...)>::operator bool() const
{
	return is_good;
}

//Specialization for Lambda Functions returning void
template<class... Args>
inline Algorithm<void(Args...)>::Algorithm()
	: is_good(false)
{
	auto placeholder = [](Args...) {};
	typedef decltype(placeholder) PL;
	lambda = new PL(placeholder);
	delLambda = [](void* l) { delete ((PL*) l); };
	copyLambda = [](void* l) -> void* { new PL(*((PL*) l)); };
	applyLambda = [](void* l, Args... args) { ((PL*) l)->operator()(args...); };
}

template<class... Args>
template<class Lambda>
inline Algorithm<void(Args...)>::Algorithm(const Lambda& lambda)
	: is_good(true)
{
	this->lambda = new Lambda(lambda);
	delLambda = [](void* l) { delete ((Lambda*) l); };
	copyLambda = [](void* l) -> void* { return new Lambda(*((Lambda*) l)); };
	applyLambda = [](void* l, Args... args) { ((Lambda*) l)->operator()(args...); };
}

template<class... Args>
inline Algorithm<void(Args...)>::Algorithm(const Algorithm<void(Args...)>& obj)
	: lambda(obj.copyLambda(obj.lambda)),
	delLambda(obj.delLambda),
	copyLambda(obj.copyLambda),
	applyLambda(obj.applyLambda),
	is_good(obj.is_good)
{
}

template<class... Args>
inline Algorithm<void(Args...)>::Algorithm(Algorithm<void(Args...)>&& tmp)
	: lambda(tmp.lambda),
	delLambda(tmp.delLambda),
	copyLambda(tmp.copyLambda),
	applyLambda(tmp.applyLambda),
	is_good(tmp.is_good)
{
	tmp.delLambda = [](void*) {};
}

template<class... Args>
inline Algorithm<void(Args...)>& Algorithm<void(Args...)>::operator=(const Algorithm<void(Args...)>& obj)
{
	delLambda(lambda);
	lambda = obj.copyLambda(obj.lambda);
	delLambda = obj.delLambda;
	copyLambda = obj.copyLambda;
	applyLambda = obj.applyLambda;
	is_good = obj.is_good;
	return *this;
}

template<class... Args>
inline Algorithm<void(Args...)>& Algorithm<void(Args...)>::operator=(Algorithm<void(Args...)>&& tmp)
{
	void* oldLambda = lambda;
	void(*oldDel)(void*) = delLambda;
	lambda = tmp.lambda;
	delLambda = tmp.delLambda;
	tmp.lambda = oldLambda;
	tmp.delLambda = oldDel;
	copyLambda = tmp.copyLambda;
	applyLambda = tmp.applyLambda;
	is_good = tmp.is_good;
	return *this;
}

template<class... Args>
template<class Lambda>
inline Algorithm<void(Args...)>& Algorithm<void(Args...)>::operator=(const Lambda& lambda)
{
	this->delLambda(this->lambda);
	this->lambda = new Lambda(lambda);
	this->delLambda = [](void* l) { delete ((Lambda*) l); };
	this->copyLambda = [](void* l) -> void* { new Lambda(*((Lambda*) l)); };
	this->applyLambda = [](void* l, Args... args) { ((Lambda*) l)->operator()(args...); };
	this->is_good = true;
	return *this;
}

template<class... Args>
inline Algorithm<void(Args...)>::~Algorithm()
{
	delLambda(lambda);
}

template<class... Args>
inline void Algorithm<void(Args...)>::operator()(Args... args)
{
	applyLambda(lambda, args...);
}

template<class... Args>
inline Algorithm<void(Args...)>::operator bool() const
{
	return is_good;
}
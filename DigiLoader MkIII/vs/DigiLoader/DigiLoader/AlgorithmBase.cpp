#include "stdafx.h"

#include "AlgorithmBase.h"
#include <tuple>

using namespace std;

AlgorithmBase::AlgorithmBase(const size_t nArgs, const std::initializer_list<const char* const>& reqs)
	: args(nArgs), returnedObject(nullptr)
{
	for(auto itr = reqs.begin(); itr != reqs.end(); ++itr)
	{
		setReq(*itr);
	}
}

AlgorithmBase::AlgorithmBase(const size_t nArgs, const std::initializer_list<const char* const>& reqs, const std::map<const char* const, AlgorithmBase*>& set)
	: args(nArgs), returnedObject(nullptr)
{
	for(auto itr = reqs.begin(); itr != reqs.end(); ++itr)
	{
		setReq(*itr);
		setReq(*itr, set.find(*itr)->second);
	}
	
}

AlgorithmBase::~AlgorithmBase()
{
	if(returnedObject != nullptr) delete returnedObject;
}

AlgorithmBase& AlgorithmBase::operator()(const std::initializer_list<void*>& args)
{
	size_t i = 0;
	for(auto itr = args.begin(); itr != args.end(); ++itr)
	{
		if(i >= args.size())
		{
			//Something about arguments given exceeds number of arguments expected
		}
		else getArgs()[i] = *itr;
		++i;
	}

	exec();
	for(size_t i = 0; i < args.size(); ++i) getArgs()[i] = nullptr;
	return *this;
}

AlgorithmBase& AlgorithmBase::operator()(const std::vector<void*>& args)
{
	size_t i = 0;
	for(auto itr = args.begin(); itr != args.end(); ++itr)
	{
		if(i >= args.size())
		{
			//Something about arguments given exceeds number of arguments expected
		}
		else getArgs()[i] = *itr;
		++i;
	}

	exec();
	for(size_t i = 0; i < args.size(); ++i) getArgs()[i] = nullptr;
	return *this;
}

bool AlgorithmBase::setReq(const char* const name, AlgorithmBase* const algo)
{
	if(reqs.find(name) == reqs.end()) return false;
	reqs[name] = algo;
	return true;
}

size_t AlgorithmBase::numArgs() const
{
	return args.size();
}



void AlgorithmBase::setReq(const char* const name)
{
	reqs[name] = nullptr;
}

AlgorithmBase& AlgorithmBase::run(const char* const name)
{
	return *(reqs[name]);
}

AlgorithmBase& AlgorithmBase::operator[](const char* const name)
{
	return run(name);
}

vector<void*>& AlgorithmBase::getArgs()
{
	return args;
}
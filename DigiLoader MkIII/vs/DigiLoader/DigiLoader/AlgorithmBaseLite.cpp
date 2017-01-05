#include "stdafx.h"

#include "AlgorithmBaseLite.h"
#include <tuple>

using namespace std;

AlgorithmBaseLite::AlgorithmBaseLite(const size_t nArgs, const std::initializer_list<const char* const>& reqs)
	: args(nArgs), returnedObject(nullptr)
{
	for(auto itr = reqs.begin(); itr != reqs.end(); ++itr)
	{
		setReq(*itr);
	}
}

AlgorithmBaseLite::AlgorithmBaseLite(const size_t nArgs, const std::initializer_list<const char* const>& reqs, const std::map<const char* const, AlgorithmBaseLite*>& set)
	: args(nArgs), returnedObject(nullptr)
{
	for(auto itr = reqs.begin(); itr != reqs.end(); ++itr)
	{
		setReq(*itr);
		setReq(*itr, set.find(*itr)->second);
	}
	
}

AlgorithmBaseLite::~AlgorithmBaseLite()
{
	if(returnedObject != nullptr) delete returnedObject;
}

AlgorithmBaseLite& AlgorithmBaseLite::operator()(const std::initializer_list<void*>& args)
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

AlgorithmBaseLite& AlgorithmBaseLite::operator()(const std::vector<void*>& args)
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

bool AlgorithmBaseLite::setReq(const char* const name, AlgorithmBaseLite* const algo)
{
	if(reqs.find(name) == reqs.end()) return false;
	reqs[name] = algo;
	return true;
}

size_t AlgorithmBaseLite::numArgs() const
{
	return args.size();
}



void AlgorithmBaseLite::setReq(const char* const name)
{
	reqs[name] = nullptr;
}

AlgorithmBaseLite& AlgorithmBaseLite::run(const char* const name)
{
	return *(reqs[name]);
}

AlgorithmBaseLite& AlgorithmBaseLite::operator[](const char* const name)
{
	return run(name);
}

vector<void*>& AlgorithmBaseLite::getArgs()
{
	return args;
}
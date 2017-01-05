#include "Algorithm.h"

using namespace std;

Algorithm::Algorithm(const string& name, const function<void*(const void*)>& function, const map<string, Algorithm*>& reqs)
	: updated(false), is_good(false), is_spawn(false), name(name), requirements(reqs), func(function), error(new string("[ERROR | " + name + "]: "))
{
	for(map<string, Algorithm*>::const_iterator i = requirements.begin(); i != requirements.end(); ++i)
	{
		if(i->second != nullptr) i->second->clients.push_back(this);
	}
}

Algorithm::Algorithm(const Algorithm& algo)
{
	*this = algo;
}

Algorithm& Algorithm::operator=(const Algorithm& algo)
{
	if(&algo != this)
	{
		updated = false;
		is_good = algo.is_good;
		name = algo.name;
		clients = algo.clients;
		is_spawn = algo.is_spawn;

		for(size_t i = 0; i < spawn.size(); ++i) delete spawn[i];
		spawn.clear();
		requirements.clear();

		for(size_t i = 0; i < algo.spawn.size(); ++i)
		{
			spawn.push_back(new Algorithm(*algo.spawn[i]));
			spawn.back()->is_spawn = true;
			requirements.insert(pair<string, Algorithm*>(spawn.back()->name, spawn.back()));
		}

		for(map<string, Algorithm*>::const_iterator i = algo.requirements.begin(); i != algo.requirements.end(); ++i)
		{
			if(i->second->is_spawn) continue;
		}
	}
	return *this;
}

Algorithm::~Algorithm()
{
	for(size_t i = 0; i < spawn.size(); ++i) delete spawn[i];
}

void* Algorithm::operator()(const void* input)
{
	return run("", input);
}

Algorithm::operator bool()
{
	if(updated) return is_good;
	setUpdateFlag(true);
	is_good = func.operator bool();
	for(map<string, Algorithm*>::const_iterator i = requirements.begin(); i != requirements.end(); ++i)
	{
		is_good = *i->second && is_good;
		if(!is_good) break;
	}
	return is_good;
}

void Algorithm::setfunc(const function<void*(const void*)>& function)
{
	setUpdateFlag(false);
	func = function;
}

void Algorithm::setreq(const string& name, Algorithm* algo)
{
	setUpdateFlag(false);
	pair<map<string, Algorithm*>::iterator, bool> result = requirements.insert(pair<string, Algorithm*>(name, algo));
	if(!result.second) result.first->second = algo;
	else
	{
		for(size_t i = 0; i < result.first->second->clients.size(); ++i)
		{
			if(result.first->second->clients[i] == this) return;
		}
		result.first->second->clients.push_back(this);
	}
}

void Algorithm::setreq(const string& name, const function<void*(const void*)>& function)
{
	spawn.push_back(new Algorithm(name, function));
	spawn.back()->is_spawn = true;
	setreq(name, spawn.back());
}

void Algorithm::voidreq(const string& name)
{
	setUpdateFlag(false);
	Algorithm* trash = requirements[name];
	requirements.erase(name);
	for(size_t i = 0; i < spawn.size(); ++i)
	{
		if(spawn[i] == trash)
		{
			delete spawn[i];
			spawn.erase(spawn.begin() + i);
			return;
		}
	}
}

void* Algorithm::run(const string& name, const void* input)
{
	if(!this->operator bool())
	{
		*error += "Algorithm \'" + name + "\' is missing!";
		return error;
	}
	if(name == "") return func(input);
	return requirements[name]->func(input);
}

void Algorithm::setUpdateFlag(bool value)
{
	if(updated == value) return;
	updated = value;
	if(!updated)
	{
		for(Algorithm* alg : clients) alg->setUpdateFlag(false);
	}
}

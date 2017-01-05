#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include<functional>
#include<map>
#include<vector>
#include<string>

class Algorithm
{
public:
	Algorithm(const std::string&, const std::function<void*(const void*)>& = std::function<void*(const void*)>(), const std::map<std::string, Algorithm*>& = std::map<std::string, Algorithm*>());
	Algorithm(const Algorithm& algo);
	Algorithm& operator=(const Algorithm& algo);
	~Algorithm();

	void* operator()(const void* = nullptr);
	void* run(const std::string& = "", const void* = nullptr);

	operator bool();
	
	void setfunc(const std::function<void*(const void*)>&);
	void setreq(const std::string&, Algorithm*);
	void setreq(const std::string&, const std::function<void*(const void*)>& = std::function<void*(const void*)>());
	void voidreq(const std::string&);
private:
	void setUpdateFlag(bool);

	bool updated, is_good, is_spawn;
	std::string name;
	std::map<std::string, Algorithm*> requirements;
	std::vector<Algorithm*> clients;
	std::vector<Algorithm*> spawn;
	std::function<void*(const void*)> func;

	std::string* error;
};

#endif
// DigiLoader MkV.cpp : Defines the entry point for the console application.
//
#include "DynamicAlgorithm.h"
#include "stdafx.h"

#include <iostream>

int test(int) { return 1; }

using namespace std;

class algo : public Algorithm<int, int>
{
public:
	int run(int&) { return 2; }
};


int main()
{
	auto d = DynamicAlgorithm<decltype(&test), int, int>(&test);
	algo a;
	int x = 0;
	cin.ignore();
	return 0;
}
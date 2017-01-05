// test.cpp : Defines the entry point for the console application.

#include "DigiLoader.h"
#include <string>
#include <functional>
#include <iostream>

#include "stdafx.h"

using namespace std;

const string desc = "this is a test";

bool test()
{
	return true;
}

int main()
{
	Algorithm<bool> a("test", test);
	cout << a();
	return 0;
}


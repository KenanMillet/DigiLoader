// DigiLoader MkV.cpp : Defines the entry point for the console application.
//
#include "Algorithm.h"
#include "stdafx.h"

#include <iostream>

using namespace std;

struct doA : public Algorithm<float>
{
	float operator()() { return 3.14f; }
};
struct doB : public Algorithm<float, float>
{
	float operator()(float k) { return k * 3.14f; }
};
struct doC : public Algorithm<void, float>
{
	void operator()(float) {}
};
struct doD : public Algorithm<>
{
	void operator()() {}
};

void doE()
{

}
void doF(int)
{

}
float doG()
{
	return 1.618f;
}
int doH(int x)
{
	return x;
}

int main()
{
	int answer = 42;
	auto doI = []() {};
	auto doJ = [](int) {};
	auto doK = [](int x) { return x + 1; };
	auto doL = [answer]() { return answer; };

	doA a;
	doB b;
	doC c;
	doD d;
	Algorithm<void(*)()> e(&doE);
	Algorithm<void(*)(int)> f(&doF);
	Algorithm<float(*)()> g(&doG);
	Algorithm<int(*)(int)> h(&doH);
	Algorithm<void()> i(doI);
	Algorithm<void(int)> j(doJ);
	Algorithm<int(int)> k(doK);
	Algorithm<int()> l(doL);

	cout << a() << endl;
	cout << b(3.14f) << endl;
	c(1.618f);
	d();
	e();
	f(24);
	cout << g() << endl;
	cout << h(12) << endl;
	i();
	j(2);
	cout << k(6) << endl;
	cout << l() << endl;

	cin.ignore();
	return 0;
}
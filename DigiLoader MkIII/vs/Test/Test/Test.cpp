// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "AlgorithmLite.h"
#include "DynamicAlgorithmLite.h"
#include <iterator>

class Test : public AlgorithmLite<int, int, int>
{
public:
	Test() : AlgorithmLite<int, int, int>({ "foo", "bar" }) {}
	Test(const std::map<const char* const, AlgorithmBaseLite*>& reqs)
		: AlgorithmLite<int, int, int>({ "foo", "bar" }, reqs) {}

protected:
	virtual void exec() {
		int x = arg<int>(0);
		int y = arg<int>(1);
		output(run("foo")(x, y) / run("bar")(x, y));
	}
};

int sub(int a, int b)
{
	return a - b;
}

using namespace std;

void test_0()
{
	int x = 2;
	int y = 3;

	DynamicAlgorithmLite<int, int, int> a(sub);

	DynamicAlgorithmLite <int, int, int> b([](int a, int b) {return a * b; });

	Test c;
	c.setReq("foo", &a);
	c.setReq("bar", &b);

	Test d({ { "foo", &b }, { "bar", &a } });

	Test e;

	cout << "x: " << x << endl;
	cout << "y: " << y << endl;
	cout << "Test A (x-y): " << a(x, y) << endl;
	cout << "Test B (x*y): " << b(x, y) << endl;
	cout << "Test C (Test A / Test B): " << c(x, y) << endl;
	cout << "Test D (Test B / Test A): " << d(x, y) << endl;
	//cout << "Test E (Incomplete): " << e(x, y);
}

int main()
{
	test_0();
	cin.ignore();
}
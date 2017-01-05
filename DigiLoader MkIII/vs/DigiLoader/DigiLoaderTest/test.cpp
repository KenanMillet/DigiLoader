#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\DigiLoader\DynamicAlgorithm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DigiLoaderTest
{		
	TEST_CLASS(AlgorithmTest)
	{
	public:
		TEST_METHOD(Basic)
		{
			DynamicAlgorithm<int, int> a([](int x) { return 2; });
			Assert::AreEqual(2, int(a(2)));
		}
	};
}
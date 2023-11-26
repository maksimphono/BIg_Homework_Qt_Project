#include "pch.h"
#include "CppUnitTest.h"
#include "../BIg_Homework_Qt_Project/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BigHomeworkTests
{
	TEST_CLASS(BigHomeworkTests)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(0, 0);
		}
	};
	TEST_CLASS(MainTests)
	{
	public:
		TEST_METHOD(test1) {
			Assert::AreEqual(2, 2);
		}
	};
}

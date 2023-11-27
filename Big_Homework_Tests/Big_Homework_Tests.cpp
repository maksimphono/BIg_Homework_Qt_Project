#include "pch.h"
#include "CppUnitTest.h"
#include "../BIg_Homework_Qt_Project/main.cpp"

//#include "C:\Qt\6.6.0\msvc2019_64\include\QtWidgets\qapplication.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BigHomeworkTests
{
	TEST_CLASS(BigHomeworkTests)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			//QApplication app;
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

#include "pch.h"
#include "CppUnitTest.h"
#include "../PKR6.10/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UT610
{
	TEST_CLASS(UT610)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Node* root = NULL;

			int p;

			p = Height(root);

			Assert::AreEqual(p, 0);
		}
	};
}
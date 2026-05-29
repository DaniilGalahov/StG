#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StGTest
{
	TEST_CLASS(TestStGLib)
	{
	public:
		TEST_METHOD(TestSanity)
		{
			Assert::IsTrue(true);
		}
	};
}
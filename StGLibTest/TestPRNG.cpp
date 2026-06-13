#include "CppUnitTest.h"
#include "Common.h"
#include "PRNG.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StGLibTest
{
	TEST_CLASS(TestPRNG)
	{
	public:
		TEST_METHOD(TestSetGetSeed)
		{
			PRNG::SetSeed(0U);
			Assert::AreEqual(0U, PRNG::GetSeed());
			PRNG::SetSeed(ToBytes(PASSWORD));
			Assert::AreEqual(3355092879U, PRNG::GetSeed());
		}

		TEST_METHOD(TestNumberWithin)
		{
			PRNG::SetSeed(ToBytes(PASSWORD));
			Assert::AreEqual(125U, PRNG::NumberWithin(255));
		}
	};
}
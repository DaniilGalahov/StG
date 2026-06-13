#include "CppUnitTest.h"
#include "Common.h"
#include "PRNG.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StGLibTest
{
	TEST_CLASS(TestPRNG)
	{
	public:
		TEST_METHOD(TestSeedFrom)
		{
			Assert::AreEqual(3355092879U, PRNG::SeedFrom(ToBytes(PASSWORD)));
		}

		TEST_METHOD(TestSetGetSeed)
		{
			PRNG prng(0U);
			Assert::AreEqual(0U, prng.GetSeed());
			prng.SetSeed(1U);
			Assert::AreEqual(1U, prng.GetSeed());
			prng.SetSeed(ToBytes(PASSWORD));
			Assert::AreEqual(3355092879U, prng.GetSeed());
		}

		TEST_METHOD(TestNumberWithin)
		{
			PRNG prng(ToBytes(PASSWORD));
			Assert::AreEqual(125U, prng.NumberWithin(255));
		}
	};
}

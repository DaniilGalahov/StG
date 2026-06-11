#include "CppUnitTest.h"
#include "Common.h"
#include "Random.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StGLibTest
{
	TEST_CLASS(TestRandom)
	{
	public:
		TEST_METHOD(TestSeed)
		{
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			uint32_t seed = Random::Seed(passwordBytes);
			Assert::AreEqual((uint32_t)3355092879, seed);
		}

		TEST_METHOD(TestNumber)
		{
			uint32_t UDPRN = Random::Number(255, 3355092879);
			Assert::AreEqual((uint32_t)125, UDPRN);
		}
	};
}
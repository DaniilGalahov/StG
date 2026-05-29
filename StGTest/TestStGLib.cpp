#include "CppUnitTest.h"
#include <opencv2/opencv.hpp>
#include "Common.h"
#include "StGLib.h"

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

		TEST_METHOD(TestEmbed)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile("..\\..\\files\\input.png");
			std::vector<uint8_t> dataBytes = LoadFromFile("..\\..\\files\\message.txt");
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<uint8_t> stegoImageBytes;
			int result = StGLib::Embed(stegoImageBytes, carrierImageBytes, dataBytes, passwordBytes);
			std::vector<uint8_t> expectedBytes = LoadFromFile("..\\..\\files\\output.png");
			Assert::AreEqual(result, 0);
			Assert::IsTrue(stegoImageBytes == expectedBytes);
		}

		TEST_METHOD(TestExtract)
		{
			std::vector<uint8_t> stegoImageBytes = LoadFromFile("..\\..\\files\\output.png");
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<uint8_t> dataBytes;
			int result = StGLib::Extract(dataBytes, stegoImageBytes, passwordBytes);
			std::vector<uint8_t> expectedBytes = LoadFromFile("..\\..\\files\\received.txt");
			Assert::AreEqual(result, 0);
			Assert::IsTrue(dataBytes == expectedBytes);
		}
	};
}
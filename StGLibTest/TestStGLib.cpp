#include "CppUnitTest.h"
#include <opencv2/opencv.hpp>
#include "Common.h"
#include "StGLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StGLibTest
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
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<uint8_t> stegoImageBytes;
			int result = StGLib::Embed(stegoImageBytes, dataBytes, carrierImageBytes, passwordBytes, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			std::vector<uint8_t> expectedBytes = LoadFromFile(STEGO_FILE_PATH);
			Assert::AreEqual(result, 0);
			Assert::IsTrue(stegoImageBytes == expectedBytes);
		}

		TEST_METHOD(TestExtract)
		{
			std::vector<uint8_t> stegoImageBytes = LoadFromFile(STEGO_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<uint8_t> dataBytes;
			int result = StGLib::Extract(dataBytes, stegoImageBytes, passwordBytes, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			std::vector<uint8_t> expectedBytes = LoadFromFile(DATA_FILE_PATH);
			Assert::AreEqual(result, 0);
			Assert::IsTrue(dataBytes == expectedBytes);
		}
	};
}
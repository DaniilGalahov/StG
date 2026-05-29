#include "CppUnitTest.h"
#include <opencv2/opencv.hpp>
#include "Common.h"
#include "Functions.h"

#define PASSWORD "People are like water - they will always find a way."

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StGTest
{
	TEST_CLASS(TestFunctions)
	{
	public:
		TEST_METHOD(TestDetermineEmbeddingMask)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile("..\\..\\files\\input.png");
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage);
			std::vector<uint8_t> embeddingMaskBytes = Convert::ToBytes(embeddingMask);
			std::vector<uint8_t> expectedMaskBytes = LoadFromFile("..\\..\\files\\embedding mask.png");
			Assert::IsTrue(expectedMaskBytes == embeddingMaskBytes);
		}

		TEST_METHOD(TestCalculateEffectiveVolume)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile("..\\..\\files\\input.png");
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			Assert::IsTrue(effectiveVolume == 469248);
		}

		TEST_METHOD(TestShuffleEmbeddingCoordinates)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile("..\\..\\files\\input.png");
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, passwordBytes, effectiveVolume);
			Assert::IsTrue(std::get<0>(shuffledCoordinates[0]) == 593);
			Assert::IsTrue(std::get<1>(shuffledCoordinates[0]) == 459);
		}

		TEST_METHOD(TestEmbed)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile("..\\..\\files\\input.png");
			std::vector<uint8_t> dataBytes = LoadFromFile("..\\..\\files\\message.txt");
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, passwordBytes, effectiveVolume);
			cv::Mat stegoImage = Functions::Embed(dataBytes, carrierImage, shuffledCoordinates);
			std::vector<uint8_t> stegoImageBytes = Convert::ToBytes(stegoImage);
			std::vector<uint8_t> expectedBytes = LoadFromFile("..\\..\\files\\output.png");
			Assert::IsTrue(stegoImageBytes == expectedBytes);
		}

		TEST_METHOD(TestExtract)
		{
			std::vector<uint8_t> stegoImageBytes = LoadFromFile("..\\..\\files\\output.png");
			cv::Mat stegoImage = Convert::ToCVMat(stegoImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(stegoImage);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, passwordBytes, effectiveVolume);
			std::vector<uint8_t> dataBytes = Functions::Extract(stegoImage, shuffledCoordinates);
			std::vector<uint8_t> expectedBytes = LoadFromFile("..\\..\\files\\received.txt");
			Assert::IsTrue(dataBytes == expectedBytes);
		}
	};
}
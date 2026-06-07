#include "CppUnitTest.h"
#include <opencv2/opencv.hpp>
#include "Common.h"
#include "Functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StGLibTest
{
	TEST_CLASS(TestFunctions)
	{
	public:
		TEST_METHOD(TestDetermineEmbeddingMask)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			std::vector<uint8_t> embeddingMaskBytes = Convert::ToBytes(embeddingMask);
			//WriteToFile(embeddingMaskBytes, EMBMASK_FILE_PATH);
			std::vector<uint8_t> expectedMaskBytes = LoadFromFile(EMBMASK_FILE_PATH);
			Assert::IsTrue(expectedMaskBytes == embeddingMaskBytes);
		}

		TEST_METHOD(TestCalculateEffectiveVolume)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			Assert::IsTrue(effectiveVolume == 1176); //bytes
		}

		TEST_METHOD(TestShuffleEmbeddingCoordinates)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, passwordBytes, effectiveVolume);
			Assert::IsTrue(std::get<0>(shuffledCoordinates[0]) == 81);
			Assert::IsTrue(std::get<1>(shuffledCoordinates[0]) == 99);
		}

		TEST_METHOD(TestEmbed)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			Assert::IsTrue(effectiveVolume >= sizeof(size_t) + dataBytes.size());
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, passwordBytes, effectiveVolume);
			cv::Mat stegoImage = Functions::Embed(dataBytes, carrierImage, shuffledCoordinates);
			std::vector<uint8_t> stegoImageBytes = Convert::ToBytes(stegoImage);
			//WriteToFile(stegoImageBytes, STEGO_FILE_PATH);
			std::vector<uint8_t> expectedBytes = LoadFromFile(STEGO_FILE_PATH);
			Assert::IsTrue(stegoImageBytes == expectedBytes);
		}

		TEST_METHOD(TestExtract)
		{
			std::vector<uint8_t> stegoImageBytes = LoadFromFile(STEGO_FILE_PATH);
			cv::Mat stegoImage = Convert::ToCVMat(stegoImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(stegoImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, passwordBytes, effectiveVolume);
			std::vector<uint8_t> dataBytes = Functions::Extract(stegoImage, shuffledCoordinates);
			std::vector<uint8_t> expectedBytes = LoadFromFile(DATA_FILE_PATH);
			Assert::IsTrue(dataBytes == expectedBytes);
		}
	};
}

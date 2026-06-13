#include "CppUnitTest.h"
#include <opencv2/opencv.hpp>
#include "Common.h"
#include "PRNG.h"
#include "Functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StGLibTest
{
	TEST_CLASS(TestFunctions)
	{
	public:

		TEST_METHOD(TestPayloadBytesQty)
		{
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			size_t qty = Functions::PayloadBytesQty(dataBytes);
			Assert::AreEqual((size_t)263, qty);
		}

		TEST_METHOD(TestPayloadBitsQty)
		{
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			size_t qty = Functions::PayloadBitsQty(dataBytes);
			Assert::AreEqual((size_t)2104, qty);
		}

		TEST_METHOD(TestPayloadPixelQty)
		{
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			size_t qty = Functions::PayloadPixelQty(dataBytes);
			Assert::AreEqual((size_t)701, qty);
		}

		TEST_METHOD(TestDetermineEmbeddingMask)
		{
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, passwordBytes, Functions::PayloadPixelQty(dataBytes));
			std::vector<uint8_t> embeddingMaskBytes = Convert::ToBytes(embeddingMask);
			//WriteToFile(embeddingMaskBytes, EMBMASK_FILE_PATH);
			std::vector<uint8_t> expectedMaskBytes = LoadFromFile(EMBMASK_FILE_PATH);
			Assert::IsTrue(expectedMaskBytes == embeddingMaskBytes);
		}

		/*
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
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			uint32_t seed = Random::Seed(passwordBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, effectiveVolume, seed);
			Assert::IsTrue(std::get<0>(shuffledCoordinates[0]) == 81);
			Assert::IsTrue(std::get<1>(shuffledCoordinates[0]) == 99);
		}

		TEST_METHOD(TestEmbed)
		{
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			uint32_t seed = Random::Seed(passwordBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			Assert::IsTrue(effectiveVolume >= sizeof(size_t) + dataBytes.size());
			std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, effectiveVolume, seed);
			cv::Mat stegoImage = Functions::Embed(dataBytes, carrierImage, shuffledCoordinates);
			std::vector<uint8_t> stegoImageBytes = Convert::ToBytes(stegoImage);
			//WriteToFile(stegoImageBytes, STEGO_FILE_PATH);
			std::vector<uint8_t> expectedBytes = LoadFromFile(STEGO_FILE_PATH);
			Assert::IsTrue(stegoImageBytes == expectedBytes);
		}

		TEST_METHOD(TestExtract)
		{
			std::vector<uint8_t> stegoImageBytes = LoadFromFile(STEGO_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat stegoImage = Convert::ToCVMat(stegoImageBytes);
			uint32_t seed = Random::Seed(passwordBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(stegoImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
			uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
			std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, effectiveVolume, seed);
			std::vector<uint8_t> dataBytes = Functions::Extract(stegoImage, shuffledCoordinates);
			std::vector<uint8_t> expectedBytes = LoadFromFile(DATA_FILE_PATH);
			Assert::IsTrue(dataBytes == expectedBytes);
		}
		*/
	};
}

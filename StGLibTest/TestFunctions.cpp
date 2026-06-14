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
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD, passwordBytes);
			std::vector<uint8_t> embeddingMaskBytes = Convert::ToBytes(embeddingMask);
			//WriteToFile(embeddingMaskBytes, EMBMASK_FILE_PATH);
			std::vector<uint8_t> expectedMaskBytes = LoadFromFile(EMBMASK_FILE_PATH);
			Assert::IsTrue(expectedMaskBytes == embeddingMaskBytes);
			Assert::AreEqual(expectedMaskBytes[0], embeddingMaskBytes[0]);
			Assert::AreEqual(expectedMaskBytes.back(), embeddingMaskBytes.back());
		}

		TEST_METHOD(TestCalculateEmbeddablePixelQty)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD, passwordBytes);
			size_t embeddablePixelQty = Functions::CalculateEmbeddablePixelQty(embeddingMask);
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			size_t expectedQty = Functions::PayloadPixelQty(dataBytes);
			Assert::IsTrue(embeddablePixelQty >= expectedQty);
		}

		TEST_METHOD(TestShuffleEmbeddingCoordinates)
		{
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD, passwordBytes);
			size_t embeddablePixelQty = Functions::CalculateEmbeddablePixelQty(embeddingMask);
			std::vector<std::tuple<uint32_t, uint32_t>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, embeddablePixelQty, passwordBytes);
			Assert::AreEqual(12U, std::get<0>(shuffledCoordinates[0]));
			Assert::AreEqual(63U, std::get<1>(shuffledCoordinates[0]));
		}

		TEST_METHOD(TestEmbed)
		{
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD, passwordBytes);
			size_t embeddablePixelQty = Functions::CalculateEmbeddablePixelQty(embeddingMask);
			Assert::IsTrue(embeddablePixelQty >= Functions::PayloadPixelQty(dataBytes));
			std::vector<std::tuple<uint32_t, uint32_t>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, embeddablePixelQty, passwordBytes);
			cv::Mat stegoImage = Functions::Embed(dataBytes, carrierImage, shuffledCoordinates);
			std::vector<uint8_t> stegoImageBytes = Convert::ToBytes(stegoImage);
			//WriteToFile(stegoImageBytes, STEGO_FILE_PATH);
			std::vector<uint8_t> expectedBytes = LoadFromFile(STEGO_FILE_PATH);
			Assert::IsTrue(expectedBytes == stegoImageBytes);
			Assert::AreEqual(expectedBytes[0], stegoImageBytes[0]);
			Assert::AreEqual(expectedBytes.back(), stegoImageBytes.back());
		}

		TEST_METHOD(TestExtract)
		{
			std::vector<uint8_t> stegoImageBytes = LoadFromFile(STEGO_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat stegoImage = Convert::ToCVMat(stegoImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(stegoImage, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD, passwordBytes);
			size_t embeddablePixelQty = Functions::CalculateEmbeddablePixelQty(embeddingMask);
			std::vector<std::tuple<uint32_t, uint32_t>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, embeddablePixelQty, passwordBytes);
			std::vector<uint8_t> dataBytes = Functions::Extract(stegoImage, shuffledCoordinates);
			std::vector<uint8_t> expectedBytes = LoadFromFile(DATA_FILE_PATH);
			Assert::IsTrue(expectedBytes == dataBytes);
			Assert::AreEqual(expectedBytes[0], dataBytes[0]);
			Assert::AreEqual(expectedBytes.back(), dataBytes.back());
		}
	};
}

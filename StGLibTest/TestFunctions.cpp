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
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, passwordBytes, EMBEDDING_TRESHOLD);
			std::vector<uint8_t> embeddingMaskBytes = Convert::ToBytes(embeddingMask);
			//WriteToFile(embeddingMaskBytes, EMBMASK_FILE_PATH);
			std::vector<uint8_t> expectedMaskBytes = LoadFromFile(EMBMASK_FILE_PATH);
			Assert::IsTrue(expectedMaskBytes == embeddingMaskBytes);
			Assert::AreEqual(expectedMaskBytes[0], embeddingMaskBytes[0]);
			Assert::AreEqual(expectedMaskBytes.back(), embeddingMaskBytes.back());
		}

		TEST_METHOD(TestDetermineEmbeddablePixelQty)
		{
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, passwordBytes, EMBEDDING_TRESHOLD);
			size_t embeddablePixelQty = Functions::CalculateEmbeddablePixelQty(embeddingMask);
			Assert::IsTrue(embeddablePixelQty >= (size_t)701);
		}

		/*
		TEST_METHOD(TestShuffleEmbeddingCoordinates)
		{
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			size_t payloadPixelQty = Functions::PayloadPixelQty(dataBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, passwordBytes, payloadPixelQty);
			std::vector<std::tuple<uint32_t, uint32_t>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, payloadPixelQty, passwordBytes);
			Assert::AreEqual(105U, std::get<0>(shuffledCoordinates[0]));
			Assert::AreEqual(70U, std::get<1>(shuffledCoordinates[0]));
		}

		TEST_METHOD(TestEmbed)
		{
			std::vector<uint8_t> dataBytes = LoadFromFile(DATA_FILE_PATH);
			std::vector<uint8_t> carrierImageBytes = LoadFromFile(CARRIER_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
			size_t payloadPixelQty = Functions::PayloadPixelQty(dataBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, passwordBytes, payloadPixelQty);
			std::vector<std::tuple<uint32_t, uint32_t>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, payloadPixelQty, passwordBytes);
			cv::Mat stegoImage = Functions::Embed(dataBytes, carrierImage, shuffledCoordinates);
			std::vector<uint8_t> stegoImageBytes = Convert::ToBytes(stegoImage);
			WriteToFile(stegoImageBytes, STEGO_FILE_PATH);
			//std::vector<uint8_t> expectedBytes = LoadFromFile(STEGO_FILE_PATH);
			//Assert::IsTrue(stegoImageBytes == expectedBytes);
		}

		TEST_METHOD(TestExtract)
		{
			std::vector<uint8_t> stegoImageBytes = LoadFromFile(STEGO_FILE_PATH);
			std::vector<uint8_t> passwordBytes = ToBytes(PASSWORD);
			cv::Mat stegoImage = Convert::ToCVMat(stegoImageBytes);
			size_t payloadPixelQty = Functions::PayloadPixelQty(dataBytes);
			cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, EMBEDDING_BLOCK_SIZE, passwordBytes, payloadPixelQty);
			std::vector<std::tuple<uint32_t, uint32_t>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, payloadPixelQty, passwordBytes);
			std::vector<uint8_t> dataBytes = Functions::Extract(stegoImage, shuffledCoordinates);
			std::vector<uint8_t> expectedBytes = LoadFromFile(DATA_FILE_PATH);
			Assert::IsTrue(dataBytes == expectedBytes);
		}
		*/
	};
}

#include "CppUnitTest.h"
#include <opencv2/opencv.hpp>
#include "Common.h"
#include "Convert.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StGTest
{
	TEST_CLASS(TestConvert)
	{
	public:
		TEST_METHOD(TestToCVMat)
		{
			std::vector<uint8_t> bytes = LoadFromFile("..\\..\\files\\input.png");
			cv::Mat expectedImage = cv::imdecode(bytes, cv::IMREAD_UNCHANGED);
			cv::Mat actualImage = Convert::ToCVMat(bytes);
			Assert::IsTrue(AreEqual(expectedImage, actualImage));
		}

		TEST_METHOD(TestImageToBytes)
		{
			cv::Mat image = cv::imread("..\\..\\files\\input.png");
			std::vector<uint8_t> expectedBytes;
			std::vector<int> params;
			params.push_back(cv::IMWRITE_PNG_COMPRESSION);
			params.push_back(3);
			cv::imencode(".png", image, expectedBytes, params);
			std::vector<uint8_t> actualBytes = Convert::ToBytes(image);
			Assert::IsTrue(expectedBytes == actualBytes);
		}

		TEST_METHOD(TestBytesToBits)
		{
			std::vector<uint8_t> bytes = { 7 };
			std::vector<bool> expectedBits = { 0,0,0,0,0,1,1,1 };
			std::vector<bool> actualBits = Convert::ToBits(bytes);
			Assert::IsTrue(expectedBits == actualBits);
		}

		TEST_METHOD(TestBitsToBytes)
		{
			std::vector<bool> bits = { 0,0,0,0,0,1,1,1 };
			std::vector<uint8_t> expectedBytes = { 7 };
			std::vector<uint8_t> actualBytes = Convert::ToBytes(bits);
			Assert::IsTrue(expectedBytes == actualBytes);
		}
	};
}
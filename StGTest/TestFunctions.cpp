#include "CppUnitTest.h"
#include <opencv2/opencv.hpp>
#include "Common.h"
#include "Functions.h"

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

	};
}
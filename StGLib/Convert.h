#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

namespace Convert
{
	cv::Mat ToCVMat(const std::vector<uint8_t>& bytes);
	std::vector<uint8_t> ToBytes(const cv::Mat& image);
	std::vector<bool> ToBits(const std::vector<uint8_t>& bytes);
	std::vector<uint8_t> ToBytes(const std::vector<bool>& bits);
}

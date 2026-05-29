#pragma once
#include <vector>
#include <tuple>
#include <random>
#include <algorithm>
#include <opencv2/opencv.hpp>

#include "SHA256.h"
#include "Convert.h"

namespace Functions
{
	cv::Mat DetermineEmbeddingMask(const cv::Mat& carrierImage, int blockSize = 8, double treshold = 0.7);

	uint32_t CalculateEffectiveVolume(const cv::Mat embeddingMask);

	std::vector<std::tuple<int, int>> ShuffleEmbeddingCoordinates(const cv::Mat& embeddingMask, const std::vector<uint8_t>& password, uint32_t effectiveVolume);

	cv::Mat Embed(const std::vector<uint8_t>& dataBytes, const cv::Mat& carrierImage, const std::vector<std::tuple<int, int>>& shuffledCoordinates);

	std::vector<uint8_t> Extract(const cv::Mat& stegoImage, const std::vector<std::tuple<int, int>>& shuffledCoordinates);
}

#pragma once
#include <vector>
#include <tuple>
#include <algorithm>
#include <opencv2/opencv.hpp>

#include "Convert.h"
#include "Random.h"

namespace Functions
{	
	cv::Mat DetermineEmbeddingMask(const cv::Mat& carrierImage, int32_t blockSize = 8, double_t treshold = 0.7);

	int32_t CalculateEffectiveVolume(const cv::Mat embeddingMask);

	std::vector<std::tuple<int32_t, int32_t>> ShuffleEmbeddingCoordinates(const cv::Mat& embeddingMask, int32_t effectiveVolume, int32_t seed);

	cv::Mat Embed(const std::vector<uint8_t>& dataBytes, const cv::Mat& carrierImage, const std::vector<std::tuple<int32_t, int32_t>>& shuffledCoordinates);

	std::vector<uint8_t> Extract(const cv::Mat& stegoImage, const std::vector<std::tuple<int32_t, int32_t>>& shuffledCoordinates);
}

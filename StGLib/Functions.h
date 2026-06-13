#pragma once
#include <vector>
#include <tuple>
#include <algorithm>
#include <opencv2/opencv.hpp>

#include "Convert.h"
#include "PRNG.h"

namespace Functions
{
	size_t PayloadBytesQty(std::vector<uint8_t> dataBytes);

	size_t PayloadBitsQty(std::vector<uint8_t> dataBytes);

	size_t PayloadPixelQty(std::vector<uint8_t> dataBytes);

	cv::Mat DetermineEmbeddingMask(const cv::Mat& carrierImage, uint32_t blockSize, const std::vector<uint8_t>& passwordBytes, size_t payloadPixelQty);

	std::vector<std::tuple<int32_t, int32_t>> ShuffleEmbeddingCoordinates(const cv::Mat& embeddingMask, int32_t effectiveVolume, const std::vector<unsigned char>& passwordBytes);

	cv::Mat Embed(const std::vector<uint8_t>& dataBytes, const cv::Mat& carrierImage, const std::vector<std::tuple<int32_t, int32_t>>& shuffledCoordinates);

	std::vector<uint8_t> Extract(const cv::Mat& stegoImage, const std::vector<std::tuple<int32_t, int32_t>>& shuffledCoordinates);
}

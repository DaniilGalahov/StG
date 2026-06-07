#include "StGLib.h"

int StGLib::Embed
(
	//out
	std::vector<uint8_t>& stegoImageBytes,

	//in
	const std::vector<uint8_t>& dataBytes,
	const std::vector<uint8_t>& carrierImageBytes,
	const std::vector<uint8_t>& passwordBytes,
	int blockSize,
	double treshold
)
{
	cv::Mat carrierImage = Convert::ToCVMat(carrierImageBytes);
	cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, blockSize, treshold);
	uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
	if (effectiveVolume < sizeof(size_t) + dataBytes.size())
	{
		return -1;
	}
	std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, passwordBytes, effectiveVolume);
	cv::Mat stegoImage = Functions::Embed(dataBytes, carrierImage, shuffledCoordinates);
	stegoImageBytes = Convert::ToBytes(stegoImage);
	return 0;
}

void StGLib::Extract
(
	//out
	std::vector<uint8_t>& dataBytes,

	//in
	const std::vector<uint8_t>& stegoImageBytes,
	const std::vector<uint8_t>& passwordBytes,
	int blockSize,
	double treshold
)
{
	cv::Mat stegoImage = Convert::ToCVMat(stegoImageBytes);
	cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(stegoImage, blockSize, treshold);
	uint32_t effectiveVolume = Functions::CalculateEffectiveVolume(embeddingMask);
	std::vector<std::tuple<int, int>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, passwordBytes, effectiveVolume);
	dataBytes = Functions::Extract(stegoImage, shuffledCoordinates);
}

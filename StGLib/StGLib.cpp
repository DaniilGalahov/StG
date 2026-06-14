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
	cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(carrierImage, blockSize, treshold, passwordBytes);
	size_t embeddablePixelQty = Functions::CalculateEmbeddablePixelQty(embeddingMask);
	if (embeddablePixelQty < Functions::PayloadPixelQty(dataBytes))
	{
		return -1;
	}
	std::vector<std::tuple<uint32_t, uint32_t>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, embeddablePixelQty, passwordBytes);
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
	cv::Mat embeddingMask = Functions::DetermineEmbeddingMask(stegoImage, blockSize, treshold, passwordBytes);
	size_t embeddablePixelQty = Functions::CalculateEmbeddablePixelQty(embeddingMask);
	std::vector<std::tuple<uint32_t, uint32_t>> shuffledCoordinates = Functions::ShuffleEmbeddingCoordinates(embeddingMask, embeddablePixelQty, passwordBytes);
	dataBytes = Functions::Extract(stegoImage, shuffledCoordinates);
}

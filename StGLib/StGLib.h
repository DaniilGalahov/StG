#pragma once
#include <vector>
#include <tuple>
#include <opencv2/opencv.hpp>

#include "Convert.h"
#include "Random.h"
#include "Functions.h"

namespace StGLib
{
	int Embed
	(
		//out
		std::vector<uint8_t>& stegoImageBytes,

		//in
		const std::vector<uint8_t>& dataBytes,
		const std::vector<uint8_t>& carrierImageBytes,
		const std::vector<uint8_t>& passwordBytes,
		int blockSize = 8,
		double treshold = 0.7
	);

	void Extract
	(
		//out
		std::vector<uint8_t>& dataBytes,

		//in
		const std::vector<uint8_t>& stegoImageBytes,
		const std::vector<uint8_t>& passwordBytes,
		int blockSize = 8,
		double treshold = 0.7
	);
}

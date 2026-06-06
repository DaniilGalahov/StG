#pragma once
#include <vector>
#include "StGLib.h"

#ifdef _WIN32
#define EXPORTABLE extern "C" __declspec(dllexport)
#else
#define EXPORTABLE extern "C"
#endif

EXPORTABLE int Embed
(
	const uint8_t* dataBytes,
	size_t dataSize,

	const uint8_t* carrierImageBytes,
	size_t carrierImageSize,

	const uint8_t* passwordBytes,
	size_t passwordSize,

	int32_t blockSize,
	double_t treshold,

	uint8_t** stegoImageBytes,
	size_t* stegoImageSize
);

EXPORTABLE int Extract
(
	const uint8_t* stegoImageBytes,
	size_t stegoImageSize,

	const uint8_t* passwordBytes,
	size_t passwordSize,

	int32_t blockSize,
	double_t treshold,

	uint8_t** dataBytes,
	size_t* dataSize
);

EXPORTABLE void FreeMemory(void* memory);
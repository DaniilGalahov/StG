#include "main.h"

int Embed
(
	const uint8_t* carrierImageBytes,
	size_t carrierImageSize,

	const uint8_t* dataBytes,
	size_t dataSize,

	const uint8_t* passwordBytes,
	size_t passwordSize,

	uint8_t** stegoImageBytes,
	size_t* stegoImageSize
)
{
	try
	{
		if
		(
			carrierImageBytes == nullptr ||
			dataBytes == nullptr ||
			passwordBytes == nullptr ||
			stegoImageBytes == nullptr ||
			stegoImageSize == nullptr
		)
		{
			return -2;
		}

		std::vector<uint8_t> carrierVector(carrierImageBytes, carrierImageBytes + carrierImageSize);
		std::vector<uint8_t> dataVector(dataBytes, dataBytes + dataSize);
		std::vector<uint8_t> passwordVector(passwordBytes, passwordBytes + passwordSize);
		std::vector<uint8_t> stegoVector;
		int result = StGLib::Embed(stegoVector, carrierVector, dataVector, passwordVector);
		*stegoImageSize = stegoVector.size();
		*stegoImageBytes = new uint8_t[*stegoImageSize];
		std::memcpy(*stegoImageBytes, stegoVector.data(), *stegoImageSize);
		return result;
	}
	catch (const std::bad_alloc&)
	{
		return -3;
	}
	catch (const std::exception&)
	{
		return -4;
	}
	catch (...)
	{
		return -5;
	}
}

int Extract
(
	const uint8_t* stegoImageBytes,
	size_t stegoImageSize,

	const uint8_t* passwordBytes,
	size_t passwordSize,

	uint8_t** dataBytes,
	size_t* dataSize
)
{
	try
	{
		if
		(
			stegoImageBytes == nullptr ||
			passwordBytes == nullptr ||
			dataBytes == nullptr ||
			dataSize == nullptr
		)
		{
			return -2;
		}

		std::vector<uint8_t> stegoVector(stegoImageBytes, stegoImageBytes + stegoImageSize);
		std::vector<uint8_t> passwordVector(passwordBytes, passwordBytes + passwordSize);
		std::vector<uint8_t> extractedVector;
		int result = StGLib::Extract(extractedVector, stegoVector, passwordVector);
		*dataSize = extractedVector.size();
		*dataBytes = new uint8_t[*dataSize];
		std::memcpy(*dataBytes, extractedVector.data(), *dataSize);
		return result;
	}
	catch (const std::bad_alloc&)
	{
		return -3;
	}
	catch (const std::exception&)
	{
		return -4;
	}
	catch (...)
	{
		return -5;
	}
}

void FreeMemory(void* memory)
{
	delete[] static_cast<uint8_t*>(memory);
}
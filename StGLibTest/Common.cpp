#include "Common.h"

std::vector<uint8_t> LoadFromFile(std::string filePath)
{
	std::ifstream file(filePath, std::ios::binary);

	if (!file)
	{
		throw std::runtime_error("Can not open file: " + filePath);
	}

	std::vector<uint8_t> bytes(std::istreambuf_iterator<char>(file), {});

	file.close();

	return bytes;
}

void WriteToFile(std::vector<uint8_t> bytes, std::string filePath)
{
	std::ofstream file(filePath, std::ios::binary);

	if (!file)
	{
		throw std::runtime_error("Can not open file: " + filePath);
	}

	file.write(reinterpret_cast<char*>(bytes.data()), bytes.size());

	file.close();
}

std::vector<uint8_t> ToBytes(std::string str)
{
	uint8_t* buffer = (uint8_t*)str.data();
	std::vector<uint8_t> bytes(buffer, buffer + str.size());
	return bytes;
}

bool AreEqual(const cv::Mat& a, const cv::Mat& b)
{
	// 1. Check dimensions and type
	if (a.empty() || b.empty() || a.size() != b.size() || a.type() != b.type())
	{
		return false;
	}

	// 2. XOR matrices; identical pixels result in 0
	cv::Mat diff;
	cv::bitwise_xor(a, b, diff);
	// 3. If any pixel is non-zero, they are not equal
	return cv::countNonZero(diff.reshape(1)) == 0;
}

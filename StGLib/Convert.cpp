#include "Convert.h"

cv::Mat Convert::ToCVMat(const std::vector<uint8_t>& bytes)
{
    cv::Mat image;
    image = cv::imdecode(bytes, cv::IMREAD_UNCHANGED);
    return image;
}

std::vector<uint8_t> Convert::ToBytes(const cv::Mat& image)
{
    std::vector<uint8_t> bytes;
    std::vector<int> params;
    params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    params.push_back(3);
    cv::imencode(".png", image, bytes, params);
    return bytes;
}

std::vector<bool> Convert::ToBits(const std::vector<uint8_t>& bytes)
{
    std::vector<bool> bits;
    bits.reserve(bytes.size() * 8);
    for (size_t i = 0; i < bytes.size(); ++i)
    {
        for (int j = 7; j >= 0; --j)
        {
            bits.push_back((bytes[i] >> j) & 1);
        }
    }

    return bits;
}

std::vector<uint8_t> Convert::ToBytes(const std::vector<bool>& bits)
{
    std::vector<uint8_t> bytes;
    bytes.reserve(bits.size() / 8);
    for (size_t i = 0; i < bits.size(); i = i + 8)
    {
        std::vector<bool>::const_iterator begin = bits.begin() + i;
        std::vector<bool>::const_iterator end = bits.begin() + i + 8;
        std::vector<bool> selection(begin, end);

        uint8_t byte = 0;
        for (size_t j = 0; j < 8 && (i + j) < bits.size(); ++j)
        {
            if (bits[i + j])
            {
                // MSB-first: Shift 1 to the correct position (7 - j) and OR it
                byte |= (1 << (7 - j));
            }
        }
        bytes.push_back(byte);
    }

    return bytes;
}
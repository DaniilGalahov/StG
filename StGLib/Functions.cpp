#include "Functions.h"

cv::Mat Functions::DetermineEmbeddingMask(const cv::Mat& carrierImage, int32_t blockSize, double_t treshold)
{
    cv::Mat yccImage;
    cv::cvtColor(carrierImage, yccImage, cv::COLOR_BGR2YCrCb);

    cv::Mat yccImageY;
    cv::extractChannel(yccImage, yccImageY, 0);

    cv::Scalar yccImageYMean, yccImageYDev;
    cv::meanStdDev(yccImageY, yccImageYMean, yccImageYDev);

    int32_t yccImageDeviation = yccImageYDev[0];

    cv::Mat embeddingMask = cv::Mat::zeros(yccImage.rows, yccImage.cols, CV_8UC1);

    int32_t rows = (int32_t)(yccImage.rows / blockSize);
    int32_t cols = (int32_t)(yccImage.cols / blockSize);

    for (int32_t r = 0; r < rows; ++r)
    {
        for (int32_t c = 0; c < cols; ++c)
        {
            cv::Rect roi(c * blockSize, r * blockSize, blockSize, blockSize);

            cv::Mat yccImageBlock = yccImage(roi);
            cv::Mat embeddingMaskBlock = embeddingMask(roi);

            cv::Mat yccImageBlockY;
            cv::extractChannel(yccImageBlock, yccImageBlockY, 0);

            cv::Scalar yccImageBlockMean, yccImageBlockDev;
            cv::meanStdDev(yccImageBlockY, yccImageBlockMean, yccImageBlockDev);

            int32_t yccImageBlockDeviation = yccImageBlockDev[0];

            if (yccImageBlockDeviation > (int32_t)(yccImageDeviation * treshold))
            {
                embeddingMaskBlock.setTo(255);
            }
        }
    }

    return embeddingMask;
}

int32_t Functions::CalculateEffectiveVolume(const cv::Mat embeddingMask)
{
    return (int32_t)((cv::countNonZero(embeddingMask) * 3)/8);
}

std::vector<std::tuple<int32_t, int32_t>> Functions::ShuffleEmbeddingCoordinates(const cv::Mat& embeddingMask, const std::vector<uint8_t>& password, int32_t effectiveVolume)
{
    int32_t loadablePixelQty = (int32_t)((effectiveVolume * 8) / 3);
    std::vector<std::tuple<int32_t, int32_t>> embeddingCoordinates;
    embeddingCoordinates.reserve(loadablePixelQty);
    for (int32_t r = 0; r < embeddingMask.rows; ++r)
    {
        for (int32_t c = 0; c < embeddingMask.cols; ++c)
        {
            if (embeddingMask.at<uchar>(r, c) == 255)
            {
                embeddingCoordinates.push_back(std::tuple<int32_t, int32_t>(r, c));
            }
        }
    }

    std::array<uint32_t, 8> hash = SHA256::Hash(password);
    size_t hashBytesLength = hash.size() * sizeof(uint32_t);
    std::vector<uint8_t> hashBytes(hashBytesLength);
    memcpy(hashBytes.data(), hash.data(), hashBytesLength);
    uint32_t seed = 0;
    for (size_t i = 0; i < hashBytes.size(); ++i)
    {
        uint8_t byte = hashBytes[i];
        seed += (seed << 8) + byte;
    }

    std::mt19937 gen(seed);
    std::uniform_int_distribution<uint32_t> dist(0, (uint32_t)embeddingCoordinates.size());
    uint32_t randomNumber = dist(gen);

    std::shuffle(embeddingCoordinates.begin(), embeddingCoordinates.end(), std::default_random_engine(randomNumber));

    return embeddingCoordinates;
}

cv::Mat Functions::Embed(const std::vector<uint8_t>& dataBytes, const cv::Mat& carrierImage, const std::vector<std::tuple<int32_t, int32_t>>& shuffledCoordinates)
{
    size_t dataLength = dataBytes.size();
    std::vector<uint8_t> dataLengthBytes(sizeof(dataLength));
    memcpy(dataLengthBytes.data(), &dataLength, sizeof(dataLength));

    std::vector<uint8_t> payloadBytes;
    payloadBytes.insert(payloadBytes.end(), dataLengthBytes.begin(), dataLengthBytes.end());
    payloadBytes.insert(payloadBytes.end(), dataBytes.begin(), dataBytes.end());

    std::vector<bool> payloadBits = Convert::ToBits(payloadBytes);
    cv::Mat stegoImage = carrierImage.clone();

    size_t pIdx = 0;
    for (size_t cIdx = 0; cIdx < shuffledCoordinates.size(); ++cIdx)
    {
        int32_t x = std::get<0>(shuffledCoordinates[cIdx]);
        int32_t y = std::get<1>(shuffledCoordinates[cIdx]);
        cv::Vec3b& pixel = stegoImage.at<cv::Vec3b>(x, y);

        for (int32_t i = 0; i < 3; ++i)
        {
            if (pIdx < payloadBits.size())
            {
                pixel[i] = pixel[i] & 0xFE | (uint8_t)payloadBits[pIdx]; //clearning LSB and adding data bit
                pIdx++;
            }
            else
            {
                return stegoImage;
            }
        }
    }

    return stegoImage;
}

std::vector<uint8_t> Functions::Extract(const cv::Mat& stegoImage, const std::vector<std::tuple<int32_t, int32_t>>& shuffledCoordinates)
{
    std::vector<bool> payloadBits;
    payloadBits.reserve(shuffledCoordinates.size() * 3);

    for (size_t cIdx = 0; cIdx < shuffledCoordinates.size(); ++cIdx)
    {
        int32_t x = std::get<0>(shuffledCoordinates[cIdx]);
        int32_t y = std::get<1>(shuffledCoordinates[cIdx]);
        const cv::Vec3b& pixel = stegoImage.at<cv::Vec3b>(x, y);

        for (int32_t i = 0; i < 3; ++i)
        {
            payloadBits.push_back(pixel[i] & 0x01); //extract bit from LSB
        }
    }

    size_t dataLength;
    size_t dataLengthOffset = sizeof(dataLength) * 8;
    std::vector<bool>::const_iterator begin = payloadBits.begin();
    std::vector<bool>::const_iterator end = payloadBits.begin() + dataLengthOffset;
    std::vector<bool> dataLengthBits(begin, end);
    std::vector<uint8_t> dataLengthBytes = Convert::ToBytes(dataLengthBits);
    memcpy(&dataLength, dataLengthBytes.data(), sizeof(dataLength));

    size_t dataOffset = dataLength * 8;
    begin = end;
    end = end + dataOffset;
    std::vector<bool> dataBits(begin, end);
    std::vector<uint8_t> dataBytes = Convert::ToBytes(dataBits);

    return dataBytes;
}

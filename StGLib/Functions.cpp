#include "Functions.h"

cv::Mat Functions::DetermineEmbeddingMask(const cv::Mat& carrierImage, int blockSize, double treshold)
{
    cv::Mat yccImage;
    cv::cvtColor(carrierImage, yccImage, cv::COLOR_BGR2YCrCb);

    cv::Mat embeddingMask = cv::Mat::zeros(yccImage.rows, yccImage.cols, CV_8UC1);

    int rows = (int)(yccImage.rows / blockSize);
    int cols = (int)(yccImage.cols / blockSize);

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            cv::Rect roi(c * blockSize, r * blockSize, blockSize, blockSize);
            cv::Mat yccImageBlock = yccImage(roi);
            if (cv::mean(yccImageBlock)[0] >= 255 * treshold)
            {
                cv::Mat embeddingMaskBlock = embeddingMask(roi);
                for (int i = 0; i < blockSize; ++i)
                {
                    for (int j = 0; j < blockSize; ++j)
                    {
                        embeddingMaskBlock.at<uchar>(i, j) = 255;
                    }
                }
            }
        }
    }

    return embeddingMask;
}

uint32_t Functions::CalculateEffectiveVolume(const cv::Mat embeddingMask)
{
    return cv::countNonZero(embeddingMask) * 3;
}

std::vector<std::tuple<int, int>> Functions::ShuffleEmbeddingCoordinates(const cv::Mat& embeddingMask, const std::vector<uint8_t>& password, uint32_t effectiveVolume)
{
    uint32_t loadablePixelQty = effectiveVolume / 3;
    std::vector<std::tuple<int, int>> embeddingCoordinates;
    embeddingCoordinates.reserve(loadablePixelQty);
    for (int r = 0; r < embeddingMask.rows; ++r)
    {
        for (int c = 0; c < embeddingMask.cols; ++c)
        {
            if (embeddingMask.at<uchar>(r, c) == 255)
            {
                embeddingCoordinates.push_back(std::tuple<int, int>(r, c));
            }
        }
    }

    std::array<uint32_t, 8> hash = SHA256::Hash(password);
    std::vector<uint8_t> hashBytes(hash.data(), hash.data() + hash.size());
    uint32_t seed = 0;
    for (size_t i = 0; i < hash.size(); ++i)
    {
        uint8_t byte = hash[i];
        seed += (seed << 8) + byte;
    }

    std::mt19937 gen(seed);
    std::uniform_int_distribution<uint32_t> dist(0, (uint32_t)embeddingCoordinates.size());
    uint32_t randomNumber = dist(gen);

    std::shuffle(embeddingCoordinates.begin(), embeddingCoordinates.end(), std::default_random_engine(randomNumber));

    return embeddingCoordinates;
}

cv::Mat Functions::Embed(const std::vector<uint8_t>& dataBytes, const cv::Mat& carrierImage, const std::vector<std::tuple<int, int>>& shuffledCoordinates)
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
        int x = std::get<0>(shuffledCoordinates[cIdx]);
        int y = std::get<1>(shuffledCoordinates[cIdx]);
        cv::Vec3b& pixel = stegoImage.at<cv::Vec3b>(x, y);

        for (int i = 0; i < 3; ++i)
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

std::vector<uint8_t> Functions::Extract(const cv::Mat& stegoImage, const std::vector<std::tuple<int, int>>& shuffledCoordinates)
{
    std::vector<bool> payloadBits;
    payloadBits.reserve(shuffledCoordinates.size() * 3);

    for (size_t cIdx = 0; cIdx < shuffledCoordinates.size(); ++cIdx)
    {
        int x = std::get<0>(shuffledCoordinates[cIdx]);
        int y = std::get<1>(shuffledCoordinates[cIdx]);
        const cv::Vec3b& pixel = stegoImage.at<cv::Vec3b>(x, y);

        for (int i = 0; i < 3; ++i)
        {
            payloadBits.push_back(pixel[i] & 0x01); //extract bit from LSB
        }
    }

    size_t dataLength;
    std::vector<bool>::const_iterator begin = payloadBits.begin();
    std::vector<bool>::const_iterator end = payloadBits.begin() + (sizeof(dataLength) * 8);
    std::vector<bool> dataLengthBits(begin, end);
    std::vector<uint8_t> dataLengthBytes = Convert::ToBytes(dataLengthBits);
    memcpy(&dataLength, dataLengthBytes.data(), sizeof(dataLength));

    begin = end;
    end = payloadBits.begin() + (sizeof(dataLength) * 8) + (dataLength * 8);
    std::vector<bool> dataBits(begin, end);
    std::vector<uint8_t> dataBytes = Convert::ToBytes(dataBits);

    return dataBytes;
}
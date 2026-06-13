#include "Functions.h"

size_t Functions::PayloadBytesQty(std::vector<uint8_t> dataBytes)
{
    return (size_t)sizeof(size_t) + dataBytes.size();
}

size_t Functions::PayloadBitsQty(std::vector<uint8_t> dataBytes)
{
    return Functions::PayloadBytesQty(dataBytes) * 8;
}

size_t Functions::PayloadPixelQty(std::vector<uint8_t> dataBytes)
{
    return (size_t)ceil(Functions::PayloadBitsQty(dataBytes) / 3);
}

cv::Mat Functions::DetermineEmbeddingMask(const cv::Mat& carrierImage, uint32_t blockSize, const std::vector<uint8_t>& passwordBytes, size_t payloadPixelQty)
{
    cv::Mat yccImage;
    cv::cvtColor(carrierImage, yccImage, cv::COLOR_BGR2YCrCb);

    cv::Mat complexityMask = cv::Mat::zeros(yccImage.rows, yccImage.cols, CV_8UC1);

    cv::Mat yccImageY;
    cv::extractChannel(yccImage, yccImageY, 0);

    cv::Mat yccImageBlock, complexityMaskBlock;
    cv::Mat yccImageBlockY;
    cv::Mat gradX, gradY, absGradX, absGradY, sobelY;

    cv::Scalar yccImageBlockMean, yccImageBlockDev, sobelMean;

    uint8_t variance, edgeEnergy, complexity;

    uint32_t rows = (uint32_t)(yccImage.rows / blockSize);
    uint32_t cols = (uint32_t)(yccImage.cols / blockSize);

    for (uint32_t r = 0; r < rows; ++r)
    {
        for (uint32_t c = 0; c < cols; ++c)
        {
            cv::Rect roi(c * blockSize, r * blockSize, blockSize, blockSize);

            yccImageBlock = yccImage(roi);
            complexityMaskBlock = complexityMask(roi);

            cv::extractChannel(yccImageBlock, yccImageBlockY, 0);
            cv::meanStdDev(yccImageBlockY, yccImageBlockMean, yccImageBlockDev);
            variance = (uint8_t)yccImageBlockDev[0];

            cv::Sobel(yccImageBlockY, gradX, CV_8UC1, 1, 0, 3);
            cv::convertScaleAbs(gradX, absGradX);
            cv::Sobel(yccImageBlockY, gradY, CV_8UC1, 0, 1, 3);
            cv::convertScaleAbs(gradY, absGradY);
            cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, sobelY);
            sobelMean = cv::mean(sobelY);
            edgeEnergy = (uint8_t)sobelMean[0];

            complexity = (uint8_t)floor((variance + edgeEnergy) / 2);

            complexityMaskBlock.setTo(complexity);
        }
    }

    //randomization of complexity mask must not be done via cv::Mat::forEach (PRNG produces errors in multy-treading calls)
    PRNG prng = PRNG(passwordBytes);
    uint32_t pixelIndex;
    for (uint32_t r = 0; r < (uint32_t)complexityMask.rows; r++)
    {
        for (uint32_t c = 0; c < (uint32_t)complexityMask.cols; c++)
        {
            pixelIndex = (r + 1) * (c + 1);
            if (prng.NumberWithin(pixelIndex) < (uint32_t)floor(pixelIndex / 2))
            {
                complexityMask.at<uint8_t>(r,c) = (uint8_t)floor(complexityMask.at<uint8_t>(r, c) / 2);
            }
        }
    }

    cv::Mat embeddingMask = cv::Mat::zeros(complexityMask.rows, complexityMask.cols, CV_8UC1);
    double  maxVal;
    cv::Point maxLoc;
    for (size_t q = 0; q < payloadPixelQty; q++)
    {
        cv::minMaxLoc(complexityMask, nullptr, &maxVal, nullptr, &maxLoc);
        embeddingMask.at<uint8_t>(maxLoc) = 255;
        complexityMask.at<uint8_t>(maxLoc) = 0;
    }

    return embeddingMask;
}

/*
int32_t Functions::CalculateEffectiveVolume(const cv::Mat embeddingMask)
{
    return (int32_t)((cv::countNonZero(embeddingMask) * 3)/8);
}
*/

std::vector<std::tuple<int32_t, int32_t>> Functions::ShuffleEmbeddingCoordinates(const cv::Mat& embeddingMask, int32_t effectiveVolume, const std::vector<unsigned char>& passwordBytes)
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

    PRNG prng = PRNG(passwordBytes);
    uint32_t udprn = prng.NumberWithin((uint32_t)embeddingCoordinates.size());

    std::shuffle(embeddingCoordinates.begin(), embeddingCoordinates.end(), std::default_random_engine(udprn));

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

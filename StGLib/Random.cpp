#include "Random.h"

uint32_t Random::Seed(const std::vector<uint8_t>& password)
{
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

    return seed;
}

uint32_t Random::Number(uint32_t distributionSize, uint32_t seed)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<uint32_t> dist(0, distributionSize);
    uint32_t UDPRN = dist(gen);
    return UDPRN;
}

#include "PRNG.h"

unsigned int PRNG::seed;
std::mt19937 PRNG::generator;

void PRNG::SetSeed(unsigned int seed)
{
    PRNG::seed = seed;
    PRNG::generator.seed(PRNG::seed);
}

void PRNG::SetSeed(const std::vector<unsigned char>& passwordBytes)
{
    std::array<unsigned int, 8> hash = SHA256::Hash(passwordBytes);

    size_t hashBytesLength = hash.size() * sizeof(unsigned int);
    std::vector<unsigned char> hashBytes(hashBytesLength);
    memcpy(hashBytes.data(), hash.data(), hashBytesLength);

    unsigned int seed = 0;
    for (size_t i = 0; i < hashBytes.size(); ++i)
    {
        unsigned char byte = hashBytes[i];
        seed += (seed << 8) + byte;
    }

    SetSeed(seed);
}

unsigned int PRNG::GetSeed()
{
    return PRNG::seed;
}

unsigned int PRNG::NumberWithin(unsigned int distributionSize)
{
    std::uniform_int_distribution<unsigned int> distribution(0, distributionSize);
    return distribution(generator);
}
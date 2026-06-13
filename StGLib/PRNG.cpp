#include "PRNG.h"

unsigned int PRNG::SeedFrom(const std::vector<unsigned char>& bytes)
{
    std::array<unsigned int, 8> hash = SHA256::Hash(bytes);

    size_t hashBytesLength = hash.size() * sizeof(unsigned int);
    std::vector<unsigned char> hashBytes(hashBytesLength);
    memcpy(hashBytes.data(), hash.data(), hashBytesLength);

    unsigned int seed = 0;
    for (size_t i = 0; i < hashBytes.size(); ++i)
    {
        unsigned char byte = hashBytes[i];
        seed += (seed << 8) + byte;
    }

    return seed;
}

PRNG::PRNG(unsigned int seed)
{
    SetSeed(seed);
}

PRNG::PRNG(const std::vector<unsigned char>& passwordBytes)
{
    SetSeed(passwordBytes);
}

void PRNG::SetSeed(unsigned int seed)
{
    PRNG::seed = seed;
    PRNG::generator = std::mt19937(PRNG::seed);
}

void PRNG::SetSeed(const std::vector<unsigned char>& passwordBytes)
{
    SetSeed(SeedFrom(passwordBytes));
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

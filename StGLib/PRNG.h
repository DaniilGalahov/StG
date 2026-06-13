#pragma once
#include <vector>
#include <random>
#include "SHA256.h"

class PRNG
{
	unsigned int seed;
	std::mt19937 generator;

public:
	static unsigned int SeedFrom(const std::vector<unsigned char>& bytes);

	PRNG(unsigned int seed);
	PRNG(const std::vector<unsigned char>& passwordBytes);
	void SetSeed(unsigned int seed);
	void SetSeed(const std::vector<unsigned char>& passwordBytes);
	unsigned int GetSeed();
	unsigned int NumberWithin(unsigned int distributionSize);
};

#pragma once
#include <vector>
#include <random>
#include "SHA256.h"

class PRNG
{
	static unsigned int seed;
	static std::mt19937 generator;

public:
	static void SetSeed(unsigned int seed);
	static void SetSeed(const std::vector<unsigned char>& password);
	static unsigned int GetSeed();
	static unsigned int NumberWithin(unsigned int distributionSize);
};
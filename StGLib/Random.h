#pragma once
#include <vector>
#include <random>
#include "SHA256.h"

namespace Random
{
	uint32_t Seed(const std::vector<uint8_t>& password);

	uint32_t Number(uint32_t distributionSize, uint32_t seed);
}

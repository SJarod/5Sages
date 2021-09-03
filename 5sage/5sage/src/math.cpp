#include "math.hpp"

#include <random>

int Math::rangeRNG(const int min, const int max)
{
	return rand() % (max - min + 1) + min;
}
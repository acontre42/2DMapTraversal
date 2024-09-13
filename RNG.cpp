#include "RNG.h"

int RNG::getNumber(int min, int max)
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}
#pragma once
#include <random>

class RNG
{
private:
	std::random_device rd;
public:
	int getNumber(int min, int max);
};


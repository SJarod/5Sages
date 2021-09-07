#pragma once

#include <string>

namespace Utils
{
	//rand between min and max (min and max included)
	int rangeRNG(const int min, const int max);

	//ask the user if yes or no
	bool yesOrNo(std::string question);
}

using namespace Utils;
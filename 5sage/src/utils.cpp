#include "utils.hpp"

#include <random>
#include <iostream>

int Utils::rangeRNG(const int min, const int max)
{
	return rand() % (max - min + 1) + min;
}

bool Utils::yesOrNo(std::string question)
{
	std::string input;
	while (!(input[0] == 'o' || input[0] == 'y' || input[0] == 'n'))
	{
		std::cout << question << " [y/n] ";
		std::getline(std::cin >> std::ws, input);
	}
	if (input[0] == 'n')
		return false;
	else
		return true;
}
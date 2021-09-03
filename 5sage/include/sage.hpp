#pragma once

#include <string>

class Table;

class Sage
{
private:

public:
	std::string	name = "";
	float		tinkingTime = 0.f;
	float		eatingTime = 0.f;
	float		waitingTime = 0.f;
	//target chopsticks
	int			stickL = 0, stickR = 0;

	Sage() = default;
	//name, target chopsticks
	Sage(std::string n, int sL, int sR);
	Sage(const Sage& s);
};
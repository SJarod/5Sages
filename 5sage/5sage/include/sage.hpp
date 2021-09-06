#pragma once

#include <string>

class Sage
{
private:

public:
	//sage's index is the same as sage's left stick
	std::string	name = "";

	float		tinkingTime = 0.f;	//amount of thinking
	float		eatingTime = 0.f;	//amount of eating
	float		waitingTime = 0.f;	//amount of waiting

	int			thinkSpeed = 0;
	int			eatSpeed = 0;

	//target chopsticks
	int			stickL = 0, stickR = 0;

	Sage() = default;
	//name, target chopsticks, action time
	Sage(std::string n, int sL, int sR, int thinkS, int eatS);
};
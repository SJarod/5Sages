#include "sage.hpp"

Sage::Sage(std::string n, int sL, int sR, int thinkT, int eatT)
{
	name = n;

	thinkSpeed = thinkT;
	eatSpeed = eatT;

	stickL = sL;
	stickR = sR;
}
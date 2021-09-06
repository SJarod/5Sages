#include "sage.hpp"

Sage::Sage(std::string n, int sL, int sR, int thinkS, int eatS)
{
	name = n;

	thinkSpeed = thinkS;
	eatSpeed = eatS;

	stickL = sL;
	stickR = sR;
}
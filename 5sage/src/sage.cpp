#include "sage.hpp"

Sage::Sage(std::string n, int sL, int sR, int thinkT, int eatT)
{
	name = n;

	thinkRythm = thinkT;
	eatRythm = eatT;

	stickL = sL;
	stickR = sR;
}
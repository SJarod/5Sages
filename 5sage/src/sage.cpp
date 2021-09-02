#include "sage.hpp"

Sage::Sage(std::string n, int sL, int sR)
{
	name = n;
	stickL = sL;
	stickR = sR;
}

Sage::Sage(const Sage& s)
{
	name = s.name;
	stickL = s.stickL;
	stickR = s.stickR;
}
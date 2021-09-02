#pragma once

#define SAGECOUNT 5

#include "sage.hpp"

#include <mutex>

class Table
{
private:
	int			chopsticks[SAGECOUNT];
	std::mutex	mutex;

public:
	Sage		sages[SAGECOUNT];

	Table();

	void think(Sage* sage);
	void eat(Sage* sage);

	void dinner();
};
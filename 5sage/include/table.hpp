#pragma once

#define SAGECOUNT 5

#include "sage.hpp"

#include <mutex>

class Table
{
private:
	std::mutex	coutMutex;
	std::mutex	chopsticksMutex[SAGECOUNT];

	std::thread threads[SAGECOUNT];

	int			chopsticks[SAGECOUNT];

public:
	Sage		sages[SAGECOUNT];

	Table();

	void think(Sage* sage, int t1, int t2);
	void eat(Sage* sage, int t);

	void dinner();
};
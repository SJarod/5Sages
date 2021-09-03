#pragma once

#define SAGECOUNT 10

//eating target time
#define EATINGTIME 10.f

//action time
#define ACTIONTIMEMIN 4
#define ACTIONTIMEMAX 10

#include "sage.hpp"

#include <mutex>

class Table
{
private:
	std::mutex	coutMutex;
	std::mutex	chopsticksMutex[SAGECOUNT];

	std::thread threads[SAGECOUNT];

	int			chopsticks[SAGECOUNT];

	float		dinnerTimeMin = 0.f;
	float		dinnerTimeMax = 10.f;

public:
	Sage		sages[SAGECOUNT];

	Table();

	//t1 : think time, t2 : eat time
	void think(Sage* sage, int t1, int t2);
	//t : eat time
	void eat(Sage* sage, int t);

	void dinner();
};
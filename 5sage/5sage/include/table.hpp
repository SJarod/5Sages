#pragma once

#define SAGECOUNT 5

//eating target time
#define EATINGTIME 20.f

//action time
#define ACTIONTIMEMIN 10
#define ACTIONTIMEMAX 11

#include "sage.hpp"

#include <mutex>

#include "ui.hpp"

class Table
{
private:
	std::mutex	coutMutex;
	std::mutex	chopsticksMutex[SAGECOUNT];
	std::thread threads[SAGECOUNT + 1];	//+1 for the UI

	int			chopsticks[SAGECOUNT];

public:
	Sage		sages[SAGECOUNT];
	UI			ui;

	Table();

	//t1 : think time, t2 : eat time
	void think(Sage* sage, int t1, int t2);
	bool canEat(Sage* sage);
	//t : eat time
	void eat(Sage* sage, int t);

	void dinner();
};
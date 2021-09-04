#pragma once

#define SAGECOUNT 5

//eating target time
#define EATINGTIME 5

//action time
#define ACTIONTIMEMIN 1
#define ACTIONTIMEMAX 3

//#define DEBUG

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

	void think(Sage* sage);

	bool canEat(Sage* sage);
	void eat(Sage* sage);

	void doneEating(Sage* sage);

	void dinner();
};
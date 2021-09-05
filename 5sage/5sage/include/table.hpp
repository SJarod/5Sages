#pragma once

//#define DEBUG

#include "sage.hpp"
#include "ui.hpp"

#include <mutex>
#include <vector>

class Table
{
private:
	unsigned int	SAGECOUNT = 5;
	float			EATINGTIME = 5.f;					//eating target time
	float			ACTIONTIMEMIN = 1.f;				//action time
	float			ACTIONTIMEMAX = 3.f;

	std::mutex					coutMutex;
	std::vector<std::mutex*>	chopsticksMutex;
	std::vector<std::thread>	threads;

	std::vector<int>			chopsticks;

	bool						canEatMore = false;		//can the sages eat more than the target time?

	void think(Sage* sage);

	bool canEat(Sage* sage);
	void eat(Sage* sage);

	void doneEating(Sage* sage);

	void dinner();

public:
	std::vector<Sage>			sages;
	UI							ui;

	Table();
	~Table();

	void setTable();
	void readyToEat();
};
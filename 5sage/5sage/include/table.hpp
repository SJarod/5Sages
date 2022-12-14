#pragma once

#include "sage.hpp"
#include "ui.hpp"

#include <mutex>
#include <vector>

#include <thread>

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

	std::vector<Sage>			sages;
	std::vector<std::string>	names;
	std::vector<int>			chopsticks;
	UI							ui;

	bool						canEatMore = false;		//can the sages eat more than the target time?

	void nameSages();

	void think(Sage* sage);

	bool canEat(Sage* sage);
	void eat(Sage* sage);

	void doneEating(Sage* sage);

	void dinner();

public:
	Table();
	~Table();

	void setTable(bool DEBUG);
	void readyToEat();
};
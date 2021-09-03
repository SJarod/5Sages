#include "table.hpp"

#include <thread>
#include <functional>

#include <iostream>

#include <chrono>

#include "math.hpp"

Table::Table()
{
	for (int i = 0; i < SAGECOUNT; ++i)
	{
		chopsticks[i] = 0;
		sages[i] = Sage("Sage" + std::to_string(i), i, (i + 1) % SAGECOUNT,
			rangeRNG(ACTIONTIMEMIN, ACTIONTIMEMAX), rangeRNG(ACTIONTIMEMIN, ACTIONTIMEMAX));
	}

	ui = UI(SAGECOUNT);
}

bool Table::canEat(Sage* sage)
{
	//try to take chopsticks
	bool okL = chopsticksMutex[sage->stickL].try_lock();
	bool okR = chopsticksMutex[sage->stickR].try_lock();

	if (okL && okR)
	{
		return true;
	}
	else //not having both chopsticks
	{
		std::string msg = sage->name + " is waiting 1s for chopsticks";

		if (okL)		//left chopstick is available
		{
			chopsticksMutex[sage->stickL].unlock();
			msg += "\b " + std::to_string(sage->stickR);
		}
		if (okR)		//right chopstick is available
		{
			chopsticksMutex[sage->stickR].unlock();
			msg += "\b " + std::to_string(sage->stickL);
		}
		else if (!okL)	//both chopsticks are not available
		{
			msg += " " + std::to_string(sage->stickL) + " and " + std::to_string(sage->stickR);
		}

		ui.changeSage(sage->stickL, 'W');

		//coutMutex.lock();
		//	std::cout << msg << std::endl;
		//coutMutex.unlock();

		//std::this_thread::sleep_for(std::chrono::seconds(1));

		return false;
	}
}

void Table::think(Sage* sage)
{
	auto start = std::chrono::steady_clock::now();

	//coutMutex.lock();
	//	std::cout << sage->name << " is thinking during " << t1 << "s" << std::endl;
	//coutMutex.unlock();
	ui.changeSage(sage->stickL, 'T');

	std::this_thread::sleep_for(std::chrono::seconds(sage->thinkRythm));

	auto end = std::chrono::steady_clock::now();
	sage->tinkingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;

	//coutMutex.lock();
	//	std::cout << std::endl << sage->name << " wants to eat" << std::endl;
	//coutMutex.unlock();

	auto startWaiting = std::chrono::steady_clock::now();

	bool ok = false;
	while (!ok)
	{
		ok = canEat(sage);
	}

	auto endWaiting = std::chrono::steady_clock::now();
	sage->waitingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;

	eat(sage);
}

void Table::eat(Sage* sage)
{
	auto start = std::chrono::steady_clock::now();

	ui.changeChopstick(sage->stickL, ++chopsticks[sage->stickL]);
	ui.changeChopstick(sage->stickR, ++chopsticks[sage->stickR]);

	ui.changeSage(sage->stickL, 'E');

	//coutMutex.lock();
	//	std::cout << sage->name << " is eating with chopsticks " << sage->stickL <<
	//		" and " << sage->stickR << " during " << t << "s" << std::endl;

	//	for (int i = 0; i < SAGECOUNT; ++i)
	//	{
	//		std::cout << chopsticks[i] << "  ";
	//	}
	//	std::cout << std::endl;
	//coutMutex.unlock();

	std::this_thread::sleep_for(std::chrono::seconds(sage->eatRythm));

	ui.changeChopstick(sage->stickL, --chopsticks[sage->stickL]);
	ui.changeChopstick(sage->stickR, --chopsticks[sage->stickR]);

	chopsticksMutex[sage->stickL].unlock();
	chopsticksMutex[sage->stickR].unlock();

	auto end = std::chrono::steady_clock::now();
	sage->eatingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;

	if (sage->eatingTime <= EATINGTIME)
		think(sage);
	else
	{
		//coutMutex.lock();
		//	std::cout << sage->name << " is done eating -------------------------------------" << std::endl;
		//coutMutex.unlock();

		ui.changeSage(sage->stickL, 'D');
	}
}

void Table::dinner()
{
	//launching threads
	for (int i = 0; i < SAGECOUNT; ++i)
		threads[i] = std::thread{ std::bind(&Table::think, this, &this->sages[i]) };

	threads[SAGECOUNT] = std::thread{ std::bind(&UI::display, &this->ui) };

	for (int i = 0; i < SAGECOUNT + 1; ++i)	//+1 for the ui
		threads[i].join();

	for (int i = 0; i < SAGECOUNT; ++i)
	{
		std::cout << sages[i].name << " eating time : " << sages[i].eatingTime << "s" <<
			", thinking time : " << sages[i].tinkingTime << "s" <<
			", waiting time : " << sages[i].waitingTime << "s" << std::endl;;
	}
}
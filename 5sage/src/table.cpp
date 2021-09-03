#include "table.hpp"

#include <thread>
#include <functional>

#include <iostream>

#include <chrono>

Table::Table()
{
	for (int i = 0; i < SAGECOUNT; ++i)
	{
		chopsticks[i] = 0;
		sages[i] = Sage("Sage" + std::to_string(i), i, (i + 1) % SAGECOUNT);
	}
}

void Table::think(Sage* sage, int t1, int t2)
{
	auto start = std::chrono::steady_clock::now();

	coutMutex.lock();
		std::cout << sage->name << " is thinking during " << t1 << "s" << std::endl;
	coutMutex.unlock();

	std::this_thread::sleep_for(std::chrono::seconds(t1));

	auto end = std::chrono::steady_clock::now();
	sage->tinkingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;

	coutMutex.lock();
		std::cout << std::endl << sage->name << " wants to eat" << std::endl;
	coutMutex.unlock();

	eat(sage, t2);
}

void Table::eat(Sage* sage, int t)
{
	auto start = std::chrono::steady_clock::now();

	//try to take chopsticks
	bool okL = chopsticksMutex[sage->stickL].try_lock();
	bool okR = chopsticksMutex[sage->stickR].try_lock();

	if (okL && okR)
	{
		chopsticks[sage->stickL] += 1;
		chopsticks[sage->stickR] += 1;

		coutMutex.lock();
			std::cout << sage->name << " is eating with chopsticks " << sage->stickL <<
				" and " << sage->stickR << " during " << t << "s" << std::endl;

			for (int i = 0; i < SAGECOUNT; ++i)
			{
				std::cout << chopsticks[i] << "  ";
			}
			std::cout << std::endl;
		coutMutex.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(t));

		chopsticks[sage->stickL] -= 1;
		chopsticks[sage->stickR] -= 1;

		chopsticksMutex[sage->stickL].unlock();
		chopsticksMutex[sage->stickR].unlock();

		auto end = std::chrono::steady_clock::now();
		sage->eatingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;
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

		coutMutex.lock();
			std::cout << msg << std::endl;
		coutMutex.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(1));

		auto end = std::chrono::steady_clock::now();
		sage->waitingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;

		eat(sage, t);
	}
}

void Table::dinner()
{
	//rand between 1 and 3
	int r[SAGECOUNT * 2];
	for (int i = 0; i < SAGECOUNT * 2; ++i)
		r[i] = rand() % 3 + 1;

	for (int i = 0; i < SAGECOUNT; ++i)
		threads[i] = std::thread{ std::bind(&Table::think, this, &this->sages[i], r[i], r[i + SAGECOUNT]) };

	for (int i = 0; i < SAGECOUNT; ++i)
		threads[i].join();

	for (int i = 0; i < SAGECOUNT; ++i)
	{
		std::cout << sages[i].name << " eating time : " << sages[i].eatingTime << "s" <<
			", thinking time : " << sages[i].tinkingTime << "s" <<
			", waiting time : " << sages[i].waitingTime << "s" << std::endl;;
	}
}
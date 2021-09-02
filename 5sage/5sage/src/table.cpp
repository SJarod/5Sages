#include "table.hpp"

#include <thread>
#include <functional>

#include <iostream>

Table::Table()
{
	for (int i = 0; i < SAGECOUNT; ++i)
	{
		chopsticks[i] = 0;

		Sage t("Sage" + std::to_string(i), i, (i + 1) % SAGECOUNT);
		sages[i] = t;
	}
}

void Table::think(Sage* sage)
{
	mutex.lock();
		std::cout << sage->name << " is thinking" << std::endl;
	mutex.unlock();

	//rand between 2 and 4
	int t = rand() % 3 + 2;

	std::this_thread::sleep_for(std::chrono::seconds(t));

	eat(sage);
}

void Table::eat(Sage* sage)
{
	if (!mutex.try_lock())
	{
		std::cout << sage->name << " is waiting" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	else
	{
		std::cout << sage->name << " is eating with " << sage->stickL << " and " <<
			sage->stickR << " chopstick" << std::endl;
		chopsticks[sage->stickL] += 1;
		chopsticks[sage->stickR] += 1;

		for (int i = 0; i < SAGECOUNT; ++i)
		{
			std::cout << chopsticks[i] << "  ";
		}

		std::cout << std::endl;
		mutex.unlock();
	}
}

void Table::dinner()
{
}
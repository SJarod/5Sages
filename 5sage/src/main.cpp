#include <iostream>

#include "table.hpp"

#include <random>
#include <time.h>

#include <thread>
#include <functional>

int main()
{
	srand(time(NULL));

	std::cout << "number of threads : " << std::thread::hardware_concurrency() << std::endl;

	Table table;
	table.dinner();

	std::thread t0{ std::bind(&Table::think, &table, &table.sages[0]) };
	std::thread t1{ std::bind(&Table::think, &table, &table.sages[1]) };
	std::thread t2{ std::bind(&Table::think, &table, &table.sages[2]) };
	std::thread t3{ std::bind(&Table::think, &table, &table.sages[3]) };
	std::thread t4{ std::bind(&Table::think, &table, &table.sages[4]) };

	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	return 0;
}
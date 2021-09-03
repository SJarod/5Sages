#include <iostream>

#include "table.hpp"

#include <random>
#include <time.h>

#include <thread>

int main()
{
	srand(time(NULL));

	std::cout << "number of threads : " << std::thread::hardware_concurrency() << std::endl;

	Table table;
	table.dinner();

	return 0;
}
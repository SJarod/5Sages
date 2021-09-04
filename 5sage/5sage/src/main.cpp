#include <iostream>

#include "table.hpp"

#include <random>
#include <time.h>

#include <thread>

#include <Windows.h>

int main()
{
	srand(time(NULL));

#ifdef DEBUG
	std::cout << "number of threads : " << std::thread::hardware_concurrency() << std::endl << std::endl;
#endif

	Table table;
	table.dinner();

	return 0;
}
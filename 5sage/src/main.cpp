#include <iostream>

#include "table.hpp"

#include <random>
#include <time.h>

#include <thread>

//leak check
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand((unsigned int)time(NULL));

#ifdef DEBUG
	std::cout << "number of threads : " << std::thread::hardware_concurrency() << std::endl << std::endl;
#endif

	Table table;
	table.setTable();
	table.readyToEat();

	return 0;
}
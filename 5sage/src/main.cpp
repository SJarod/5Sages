#include <iostream>

#include "table.hpp"

#include <random>
#include <time.h>

#include <thread>

//leak check
#include <stdlib.h>
#include <crtdbg.h>

#include "utils.hpp"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand((unsigned int)time(NULL));

	std::cout << "Do you need a DEBUG display [y/n]?" << std::endl;
	std::cout << "[y] : DEBUG mode - show text instead of an UI" << std::endl;
	std::cout << "[n] : PLAY mode - show a minimalist UI" << std::endl;

	bool debug = yesOrNo("?");

	std::cout << "\nPlease DO NOT enter text when program asks for NUMBERS\n" << std::endl;

	if (debug)
		std::cout << "number of threads : " << std::thread::hardware_concurrency() << std::endl << std::endl;

	Table table;
	table.setTable(debug);
	table.readyToEat();

	return 0;
}
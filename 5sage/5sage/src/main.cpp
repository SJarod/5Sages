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

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 9);	std::cout << "T";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " : thinking" << std::endl;
	SetConsoleTextAttribute(hConsole, 12);	std::cout << "E";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " : eating" << std::endl;
	SetConsoleTextAttribute(hConsole, 10);	std::cout << "W";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " : waiting" << std::endl;
	SetConsoleTextAttribute(hConsole, 15);	std::cout << "D";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " : done" << std::endl << std::endl;
	std::cout << "0 : chopstick available" << std::endl;
	SetConsoleTextAttribute(hConsole, 12);	std::cout << "1";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " : chopstick unavailable" << std::endl;

	Table table;
	table.dinner();

	return 0;
}
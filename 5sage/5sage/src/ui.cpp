#include "ui.hpp"

#include <iostream>

#include <chrono>

UI::UI(int sageCount, bool DEBUG)
{
	this->DEBUG = DEBUG;

	for (int i = 0; i < sageCount; ++i)
	{
		sageState.push_back('T');
		chopstickState.push_back(0);
	}
}

void UI::changeSage(const int index, const char state)
{
	sageState[index] = state;
}

void UI::changeChopstick(const int index, const int state)
{
	chopstickState[index] = state;
}

void UI::display()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	makeCursorInvisible(hConsole);

	COORD startPos = getConsoleCursorPosition(hConsole);
	auto dinnerStart = std::chrono::steady_clock::now();

	while (!finished)
	{
		displayTimer(dinnerStart);

		std::cout << std::endl << "  ";

		displaySageState(hConsole);

		std::cout << std::endl;

		displayChopstickState(hConsole);

		std::cout << std::endl << std::endl;

		finished = true;
		for (char c : sageState)
		{
			if (c != 'D')
			{
				finished = false;
				break;
			}
		}

		resetCursorPosition(hConsole, startPos);
	}
}

void UI::displayTimer(std::chrono::steady_clock::time_point dinnerStart)
{
	auto dinnerNow = std::chrono::steady_clock::now();
	std::cout << "Timer : ";
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(dinnerNow - dinnerStart).count() / 1000.f;
	std::cout << "s" << std::endl;
}

void UI::displaySageState(HANDLE hConsole)
{
	//display sages's state
	for (char c : sageState)
	{
		switch (c)
		{
		case 'E':
			SetConsoleTextAttribute(hConsole, 12);
			break;
		case 'W':
			SetConsoleTextAttribute(hConsole, 10);
			break;
		case 'T':
			SetConsoleTextAttribute(hConsole, 9);
			break;
		case 'D':
			SetConsoleTextAttribute(hConsole, 15);
			break;
		}

		std::cout << c << "  ";
		SetConsoleTextAttribute(hConsole, 7);
	}
}

void UI::displayChopstickState(HANDLE hConsole)
{
	//display chopsticks's state
	if (sageState[sageState.size() - 1] == 'E')
	{
		std::cout << "   ";
		for (int i = 1; i < chopstickState.size(); ++i)
		{
			if (chopstickState[i] == 1)
				SetConsoleTextAttribute(hConsole, 12);
			else
				SetConsoleTextAttribute(hConsole, 15);

			std::cout << chopstickState[i] << "  ";
			SetConsoleTextAttribute(hConsole, 7);
		}
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << chopstickState[chopstickState.size() - 1];
		SetConsoleTextAttribute(hConsole, 7);
	}
	else
	{
		for (int i : chopstickState)
		{
			if (i == 1)
				SetConsoleTextAttribute(hConsole, 12);
			else
				SetConsoleTextAttribute(hConsole, 15);

			std::cout << i << "  ";
			SetConsoleTextAttribute(hConsole, 7);
		}
		std::cout << "   ";
	}
}

void UI::makeCursorInvisible(HANDLE hConsole)
{
	//make the cursor invisible
	CONSOLE_CURSOR_INFO cInfo;
	cInfo.dwSize = 100;
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cInfo);
}

COORD UI::getConsoleCursorPosition(HANDLE hConsole)
{
	//position of the console cursor
	CONSOLE_SCREEN_BUFFER_INFO cInfo;
	GetConsoleScreenBufferInfo(hConsole, &cInfo);

	return cInfo.dwCursorPosition;
}

void UI::resetCursorPosition(HANDLE hConsole, COORD startPos)
{
	if (!finished)
		SetConsoleCursorPosition(hConsole, startPos);	//place the cursor on starting line
}
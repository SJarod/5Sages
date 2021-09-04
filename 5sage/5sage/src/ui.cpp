#include "ui.hpp"

#include <iostream>

#include <Windows.h>

UI::UI(int sageCount)
{
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

	//make the cursor invisible
	CONSOLE_CURSOR_INFO cInfo;
	cInfo.dwSize = 100;
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cInfo);

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

	while (!finished)
	{
		std::cout << std::endl << "  ";

		//display sages's state
		for (char c : sageState)
		{
			if (c == 'E')
				SetConsoleTextAttribute(hConsole, 12);
			else if (c == 'W')
				SetConsoleTextAttribute(hConsole, 10);
			else if (c == 'T')
				SetConsoleTextAttribute(hConsole, 9);

			std::cout << c << "  ";
			SetConsoleTextAttribute(hConsole, 15);
		}

		std::cout << std::endl;

		//display chopsticks's state
		if (sageState[sageState.size() - 1] == 'E')
		{
			std::cout << "   ";
			for (int i = 1; i < chopstickState.size(); ++i)
			{
				if (chopstickState[i] == 1)
					SetConsoleTextAttribute(hConsole, 12);

				std::cout << chopstickState[i] << "  ";
				SetConsoleTextAttribute(hConsole, 15);
			}
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << chopstickState[chopstickState.size() - 1];
			SetConsoleTextAttribute(hConsole, 15);
		}
		else
		{
			for (int i : chopstickState)
			{
				if (i == 1)
					SetConsoleTextAttribute(hConsole, 12);

				std::cout << i << "  ";
				SetConsoleTextAttribute(hConsole, 15);
			}
			std::cout << "   ";
		}

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

		//erasing lines
		if (!finished)
		{
			//number of std::endl
			for (int i = 0; i < 5; ++i)
			{
				std::cout << "\r\x1b[A";	//erasing line then set cursor on upper line
			}
			std::cout << std::endl;
		}
	}
}
#pragma once

#include <vector>
#include <Windows.h>

#include <chrono>

class UI
{
private:
	//UI display does not need mutex (for std::cout) because it is the only thread printing on the console
	std::vector<char>	sageState;
	std::vector<int>	chopstickState;

	bool				finished = false;

public:
	UI() = default;
	UI(int sageCount);

	void	changeSage(const int index, const char state);
	void	changeChopstick(const int index, const int state);

	void	display();

	void	displayTimer(std::chrono::steady_clock::time_point dinnerStart);
	void	displaySageState(HANDLE hConsole);
	void	displayChopstickState(HANDLE hConsole);

	void	makeCursorInvisible(HANDLE hConsole);
	COORD	getConsoleCursorPosition(HANDLE hConsole);
	void	resetCursorPosition(HANDLE hConsole, COORD startPos);
};
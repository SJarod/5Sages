#pragma once

#include <vector>
#include <Windows.h>

class UI
{
private:
	std::vector<char>	sageState;
	std::vector<int>	chopstickState;

	bool				finished = false;

public:
	UI() = default;
	UI(int sageCount);

	void changeSage(const int index, const char state);
	void changeChopstick(const int index, const int state);

	void display();

	void displaySageState(HANDLE hConsole);
	void displayChopstickState(HANDLE hConsole);
	void eraseLines();
};
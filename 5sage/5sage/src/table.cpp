#include "table.hpp"

#include <functional>
#include <iostream>
#include <chrono>
#include <Windows.h>

#include "utils.hpp"

Table::Table()
{
	std::cout << "Dieu a organise un repas ou il a invite ses sages preferes." << std::endl;
	std::cout << "Combien de sages sont invites? ";
	unsigned int count;
	std::cin >> count;
	if (count <= 1)
	{
		count = 2;
		std::cout << "2" << std::endl;
	}
	SAGECOUNT = count;

	nameSages();

	std::cout << "Pendant combien de temps (en secondes) les sages doivent-ils manger? ";
	std::cin >> EATINGTIME;

	std::cout << "Pendant combien de temps (en secondes) les sages pensent/mangent-ils au minimum? ";
	std::cin >> ACTIONTIMEMIN;

	std::cout << "Pendant combien de temps (en secondes) les sages pensent/mangent-ils au maximum? ";
	std::cin >> ACTIONTIMEMAX;

	canEatMore = yesOrNo("Les sages peuvent-ils manger plus que le temps voulu?");

	std::cout << std::endl;
}

Table::~Table()
{
	for (std::mutex* m : chopsticksMutex)
		delete m;

	chopsticksMutex.clear();
}

void Table::setTable(bool DEBUG)
{
	for (unsigned int i = 0; i < SAGECOUNT; ++i)
	{
		chopsticksMutex.push_back(new std::mutex);

		threads.push_back(std::thread());

		int thinkT = rangeRNG((int)ACTIONTIMEMIN, (int)ACTIONTIMEMAX);
		int eatT = rangeRNG((int)ACTIONTIMEMIN, (int)ACTIONTIMEMAX);
		sages.push_back(Sage(names[i], i, (i + 1) % SAGECOUNT, thinkT, eatT));

		chopsticks.push_back(0);
	}

	threads.push_back(std::thread()); //+1 for the UI
	ui = UI(SAGECOUNT, DEBUG);
}

void Table::nameSages()
{
	for (unsigned int i = 0; i < SAGECOUNT; ++i)
	{
		names.push_back("Sage" + std::to_string(i));
	}

	std::cout << std::endl << "Entrer \"Je n'ai plus d'inspi\" pour arreter de nommer les sages." << std::endl;

	for (unsigned int i = 0; i < SAGECOUNT; ++i)
	{
		std::cout << "nom du " << i + 1 << "ieme sage : ";

		std::string input;
		std::getline(std::cin >> std::ws, input);
		if (input == "Je n'ai plus d'inspi")
			break;

		names[i] = input;
	}

	std::cout << std::endl;
}

void Table::think(Sage* sage)
{
	//start of thread
	auto start = std::chrono::steady_clock::now();

	if (ui.DEBUG)
	{
		coutMutex.lock();
			std::cout << sage->name << " is thinking during " << sage->thinkSpeed << "s" << std::endl;
		coutMutex.unlock();
	}

	ui.changeSage(sage->stickL, 'T');

	std::this_thread::sleep_for(std::chrono::seconds(sage->thinkSpeed));

	auto end = std::chrono::steady_clock::now();
	sage->tinkingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;

	if (ui.DEBUG)
	{
		coutMutex.lock();
			std::cout << std::endl << sage->name << " wants to eat" << std::endl;
		coutMutex.unlock();
	}

	auto startWaiting = std::chrono::steady_clock::now();

	bool ok = false;
	while (!ok)
	{
		ok = canEat(sage);
	}

	auto endWaiting = std::chrono::steady_clock::now();
	sage->waitingTime += std::chrono::duration_cast<std::chrono::milliseconds>(endWaiting - startWaiting).count() / 1000.f;

	eat(sage);
}

bool Table::canEat(Sage* sage)
{
	//try to take chopsticks
	bool okL = chopsticksMutex[sage->stickL]->try_lock();
	bool okR = chopsticksMutex[sage->stickR]->try_lock();

	if (okL && okR)
	{
		return true;
	}
	else //not having both chopsticks
	{
		std::string msg = sage->name + " is waiting for chopsticks";

		if (okL)		//left chopstick is available
		{
			chopsticksMutex[sage->stickL]->unlock();
			msg += "\b " + std::to_string(sage->stickR);
		}
		if (okR)		//right chopstick is available
		{
			chopsticksMutex[sage->stickR]->unlock();
			msg += "\b " + std::to_string(sage->stickL);
		}
		else if (!okL)	//both chopsticks are not available
		{
			msg += " " + std::to_string(sage->stickL) + " and " + std::to_string(sage->stickR);
		}

		ui.changeSage(sage->stickL, 'W');

		if (ui.DEBUG)
		{
			coutMutex.lock();
			std::cout << msg << std::endl;
			coutMutex.unlock();

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		return false;
	}
}

void Table::eat(Sage* sage)
{
	auto start = std::chrono::steady_clock::now();

	//chopsticks already locked in canEat()
	ui.changeChopstick(sage->stickL, ++chopsticks[sage->stickL]);
	ui.changeChopstick(sage->stickR, ++chopsticks[sage->stickR]);

	ui.changeSage(sage->stickL, 'E');

	if (ui.DEBUG)
	{
		coutMutex.lock();
			std::cout << sage->name << " is eating with chopsticks " << sage->stickL <<
				" and " << sage->stickR << " during " << sage->eatSpeed << "s" << std::endl;

			std::cout << "chopsticks : ";
			for (unsigned int i = 0; i < SAGECOUNT; ++i)
			{
				std::cout << chopsticks[i] << "  ";
			}
			std::cout << std::endl;
		coutMutex.unlock();
	}

	std::this_thread::sleep_for(std::chrono::seconds(sage->eatSpeed));

	ui.changeChopstick(sage->stickL, --chopsticks[sage->stickL]);
	ui.changeChopstick(sage->stickR, --chopsticks[sage->stickR]);

	chopsticksMutex[sage->stickL]->unlock();
	chopsticksMutex[sage->stickR]->unlock();

	auto end = std::chrono::steady_clock::now();
	sage->eatingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;

	doneEating(sage);
}

void Table::doneEating(Sage* sage)
{
	if (sage->eatingTime < EATINGTIME)
	{
		if (!canEatMore)
		{
			//cannot eat more than the eating target time
			if (sage->eatingTime + (float)sage->eatSpeed > EATINGTIME)
				sage->eatSpeed = (int)EATINGTIME - (int)sage->eatingTime;
		}

		think(sage);
	}
	else
	{
		if (ui.DEBUG)
		{
			coutMutex.lock();
				std::cout << sage->name << " is done eating -------------------------------------" << std::endl;
			coutMutex.unlock();
		}

		ui.changeSage(sage->stickL, 'D');
		//end of thread
	}
}

void Table::readyToEat()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!ui.DEBUG)
	{
		std::cout << "Voici les regles : " << std::endl;
		SetConsoleTextAttribute(hConsole, 9);	std::cout << "T";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << " : thinking" << std::endl;
		SetConsoleTextAttribute(hConsole, 12);	std::cout << "E";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << " : eating" << std::endl;
		SetConsoleTextAttribute(hConsole, 10);	std::cout << "W";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << " : waiting" << std::endl;
		SetConsoleTextAttribute(hConsole, 15);	std::cout << "D";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << " : done" << std::endl << std::endl;
		SetConsoleTextAttribute(hConsole, 15);	std::cout << "0";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << " : chopstick available" << std::endl;
		SetConsoleTextAttribute(hConsole, 12);	std::cout << "1";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << " : chopstick unavailable" << std::endl << std::endl;
	}

	bool commence = false;
	while (!commence)
	{
		commence = yesOrNo("Le dinner peut-il commencer?");
	}

	dinner();
}

void Table::dinner()
{
	std::cout << std::endl << "Le dinner des " << SAGECOUNT << " sages peut commencer." << std::endl << std::endl;

	//launching threads for sages
	for (unsigned int i = 0; i < SAGECOUNT; ++i)
		threads[i] = std::thread{ std::bind(&Table::think, this, &this->sages[i]) };

	//launching thread for ui (only if not in debug mode)
	if (!ui.DEBUG)
		threads[SAGECOUNT] = std::thread{ std::bind(&UI::display, &this->ui) };

	//joining threads
	if (ui.DEBUG)
	{
		for (unsigned int i = 0; i < SAGECOUNT; ++i)
			threads[i].join();
	}
	else
	{
		for (unsigned int i = 0; i < SAGECOUNT + 1; ++i)	//+1 for the ui
			threads[i].join();
	}

	for (unsigned int i = 0; i < SAGECOUNT; ++i)
	{
		std::cout << sages[i].name << "'s eating time : " << sages[i].eatingTime << "s" <<
			", thinking time : " << sages[i].tinkingTime << "s" <<
			", waiting time : " << sages[i].waitingTime << "s" << std::endl;;
	}

	std::cout << std::endl;
	bool quit = false;
	while (!quit)
	{
		quit = yesOrNo("Do you want to quit the application?");
	}
}
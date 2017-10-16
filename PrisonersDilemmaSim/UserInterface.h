#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

struct menuItem {
	string name;
	void* function;

};

class UserInterface
{
public:
	UserInterface();
	~UserInterface();


	/* Displays the given message in a bordered format */
	void display(string message); 

	/* Displays the main menu options */
	void mainMenu();

	/*  */
	inline string gatherInput() {
		string n;
		cout << ">> ";
		getline(cin, n);

		return n;
	}
	

protected:
	string title =
		"***************************************************\n"
		"***************************************************\n"
		"|| ______     _                           _      ||\n"
		"|| | ___ \\   (_)                         ( )     ||\n"
		"|| | |_/ / __ _ ___  ___  _ __   ___ _ __|/ ___  ||\n"
		"|| |  __/ '__| / __|/ _ \\| '_ \\ / _ \\ '__| / __| ||\n"
		"|| | |  | |  | \\__ \\ (_) | | | |  __/ |    \\__ \\ ||\n"
		"|| \\_|  |_|  |_|___/\\___/|_| |_|\\___|_|    |___/ ||\n"
		"||                                               ||\n"
		"|| ______ _ _                                    ||\n"
		"|| |  _  (_) |                                   ||\n"
		"|| | | | |_| | ___ _ __ ___  _ __ ___   __ _     ||\n"
		"|| | | | | | |/ _ \\ '_ ` _ \\| '_ ` _ \\ / _` |    ||\n"
		"|| | |/ /| | |  __/ | | | | | | | | | | (_| |    ||\n"
		"|| |___/ |_|_|\\___|_| |_| |_|_| |_| |_|\\__,_|    ||\n"
		"||                                               ||\n";

	string space = "||                                               ||\n";
	string divider =
		"***************************************************\n"
		"***************************************************\n";

	static const int optionNum = 3;
	string options[optionNum] = { "0. Exit", " 1. Manually Enter Strategy", "2. Run Tournament"};

	SMALL_RECT windowSize;
	HANDLE currentConsole;
};


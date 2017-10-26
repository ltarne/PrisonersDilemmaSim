#include "UserInterface.h"



UserInterface::UserInterface() {
	currentConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	windowSize = { 0, 0, 50, 50 };

	if (!SetConsoleWindowInfo(currentConsole, TRUE, &windowSize)) {
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
	}
	if (!SetConsoleTitle(L"Prisoner's Dilemma Sim")) {
		cout << "SetConsoleTitle failed with error " << GetLastError() << endl;
	}
	cout << title;
}


UserInterface::~UserInterface() {
}


void UserInterface::display(string message) {
	int gap = 45;
	if (message.length() <= gap) {
		//Calculate spacing
		gap = (gap - message.length() + 2) / 2;
		//Tenary operator adds a space at the end if the message is an even length
		cout << "||" << string(gap, ' ') << message << string(gap, ' ') << (((message.length() % 2) == 0)?" ":"") << "||\n";
	}
	else {
		//Wrap text around
		cout << "|| " << message.substr(0, 45) << " ||\n";
		display(message.substr(45, message.length() - 1));
	}

}


void UserInterface::mainMenu() {
	cout << divider;
	display("Main Menu");
	display("---------");
	for (int i = 0; i < optionNum; ++i) {
		display(options[i]);
		display(" ");
	}
	cout << divider;
}

string UserInterface::gatherString() {


	string n;
	cout << ">> ";
	
	getline(cin, n);

	cin.clear();
	//cin.ignore(10000, '\n');
	return n;
}

int UserInterface::gatherInteger() {
	int n;
	cout << ">> ";
	
	cin >> n;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		return -1;
	}
	cin.clear();
	cin.ignore(10000, '\n');

	return n;
}
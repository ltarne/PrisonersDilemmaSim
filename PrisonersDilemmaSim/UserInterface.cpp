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

void UserInterface::displayReport(vector<Report<unsigned int>> report) {
	//Key
	displayDivider();
	display("Key");
	for (int i = 0; i < report.size(); ++i) {
		display(report[i].getName());
		display("-------------------");
		for (int j = 0; j < report[i].getMemberNames().size(); ++j) {
			display(report[i].getMemberNames()[j]);
		}
	}
	displayDivider();
	display("Overall Score");
	for (int x = 0; x < report.size(); ++x) {
		display(report[x].getName() + to_string(report[x].getFinalResult()));
	}
	displayDivider();
	display("Would you like to see the detailed results? \ny/n");
	string detail = "";
	while (detail != "y" && detail != "n") {
		detail = gatherString();
	}
	if (detail == "y") {
		display("Game Breakdown");
		for (int x = 0; x < report.size(); ++x) {


			for (int i = 0; i < report[x].getGameOutcomes().size(); ++i) {
				display(report[x].getGameOutcomes()[i].first);
				display("-----------");
				display("ALLOUTCOMES_W: " + to_string(report[x].getGameOutcomes()[i].second[0]));
				display("ALLOUTCOMES_X: " + to_string(report[x].getGameOutcomes()[i].second[1]));
				display("ALLOUTCOMES_Y: " + to_string(report[x].getGameOutcomes()[i].second[2]));
				display("ALLOUTCOMES_Z: " + to_string(report[x].getGameOutcomes()[i].second[3]));
				display("ALLOUTCOMES_A: " + to_string(report[x].getGameOutcomes()[i].second[4]));
				display("ALLOUTCOMES_B: " + to_string(report[x].getGameOutcomes()[i].second[5]));
				display("ALLOUTCOMES_C: " + to_string(report[x].getGameOutcomes()[i].second[6]));
				if (report[x].getSpyVariables().size() != 0) {
					display("Total Spies: " + to_string(report[x].getSpyVariables()[i].second.first));
					display("Total Swaps: " + to_string(report[x].getSpyVariables()[i].second.second));
				}

				display(" ");
			}
		}
	}

	display("Would you like to print to file? y/n");
	detail = "";
	while (detail != "y" && detail != "n") {
		detail = gatherString();
	}
	if (detail == "y") {
		display("Enter full name for file: ");
		string fileName = gatherString();

		for (int i = 0; i < report.size(); ++i) {
			report[i].toFile(fileName);
		}
	}

	

	
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
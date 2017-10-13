#include"UserInterface.h"

int main() {
	UserInterface ui = UserInterface();

	int command = -1;

	while (command != 0) {
		ui.mainMenu();
		command = ui.gatherInput();
	}

	return 0;
}
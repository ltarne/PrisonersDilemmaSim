
#include "StrategyGenerator.h"
#include "Tournament.h"
#include "Interpreter.h"

int main() {
	UserInterface ui = UserInterface();
	StrategyGenerator strategyGenerator = StrategyGenerator(&ui);
	Interpreter interpreter = Interpreter(&ui);
	Tournament tournament = Tournament(&interpreter);
	Prisoner* temp = NULL;

	Prisoner* prisonerX;
	Prisoner* prisonerY;

	srand(time(NULL));

	int command = -1;

	while (command != 0) {
		ui.mainMenu();

		try {
			command = stoi(ui.gatherInput());
		}
		catch(exception e) {
			//If user enters a string set command to -1
			command = -1;
		}

		switch (command) {
		case 0:
			break;
		case 1:
			strategyGenerator.writeManualStrategy();
			break;

		case 2:
			ui.display("Enter file path: ");
			temp = interpreter.interpretFile(ui.gatherInput());
			if (temp) {
				ui.display("Strategy file is valid!");
			}
			break;

		case 3:
			ui.display("Enter file path for prisoner x: ");
			prisonerX = interpreter.interpretFile(ui.gatherInput());

			ui.display("Enter file path for prisoner y: ");
			prisonerY = interpreter.interpretFile(ui.gatherInput());

			tournament.executeGame(prisonerX, prisonerY);
			break;

		default:
			//If user enters a string or a invalid number a warning will be displayed
			ui.display("Invalid option!");
			break;
		}
		

		

	}

	if (temp) {
		delete temp;
	}

	return 0;
}
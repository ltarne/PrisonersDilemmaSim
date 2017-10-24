
#include "StrategyGenerator.h"
#include "Tournament.h"

int main() {
	UserInterface ui = UserInterface();
	
	Interpreter interpreter = Interpreter(&ui);
	StrategyGenerator strategyGenerator = StrategyGenerator(&ui, &interpreter);
	Tournament tournament = Tournament(&interpreter);

	Prisoner* temp = NULL;
	Prisoner* prisonerX = NULL;
	Prisoner* prisonerY = NULL;

	string baseName;
	int n = 0;
	int iterations = 0;

	srand(time(NULL));

	int command = -1;

	while (command != 0) {
		ui.mainMenu();
		command = ui.gatherInteger();
		
		switch (command) {
		case 0:
			break;
		case 1:
			strategyGenerator.writeManualStrategy();
			break;

		case 2:
			ui.display("Enter file path: ");
			temp = interpreter.interpretFile(ui.gatherString());
			if (temp) {
				ui.display("Strategy file is valid!");
				delete temp;
			}
			break;

		case 3:
			ui.display("Enter file path for prisoner x: ");
			prisonerX = interpreter.interpretFile(ui.gatherString());

			ui.display("Enter file path for prisoner y: ");
			prisonerY = interpreter.interpretFile(ui.gatherString());

			tournament.executeGame(prisonerX, prisonerY, 200);

			tournament.resetTournament();

			delete prisonerX;
			prisonerX = NULL;
			delete prisonerY;
			prisonerY = NULL;
			break;

		case 4:
			ui.display("Enter the number of files to be tested: ");
			n = ui.gatherInteger();
			ui.display("Enter base name for files: ");
			baseName = ui.gatherString();

			ui.display("Enter number of iterations: ");
			iterations = ui.gatherInteger();

			tournament.loadTournament(baseName, n);
			tournament.executeTournament(iterations);
			tournament.resetTournament();
			break;

		case 5:
			strategyGenerator.generateStrategies(10);
			break;
		default:
			//If user enters a string or a invalid number a warning will be displayed
			ui.display("Invalid option!");
			break;
		}

	}

	return 0;
}
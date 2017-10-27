/* Main file
* Author: Luke Burton 140274882
* Date: 27/10/2017
*/
#include "StrategyGenerator.h"
#include "Tournament.h"

int main() {
	UserInterface ui = UserInterface();
	
	Interpreter interpreter = Interpreter(&ui);
	StrategyGenerator strategyGenerator = StrategyGenerator(&ui, &interpreter);
	Tournament tournament = Tournament(&interpreter, &ui);

	string baseName;
	int n = 0;
	int iterations = 0;

	srand(time(NULL));

	int command = -1;
	//Command -1 is no command
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
			strategyGenerator.generateStrategies(10);
			break;

		case 3:
			tournament.executeTournament();

			break;

		case 4:
			tournament.executeGangTournament();
			break;

		default:
			//If user enters a string or a invalid number a warning will be displayed
			ui.display("Invalid option!");
			break;
		}

	}

	return 0;
}
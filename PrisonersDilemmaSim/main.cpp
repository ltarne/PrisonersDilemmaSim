
#include "StrategyGenerator.h"
#include "Tournament.h"

int main() {
	UserInterface* ui = new UserInterface();
	StrategyGenerator strategyGenerator = StrategyGenerator(ui);


	int command = -1;

	while (command != 0) {
		ui->mainMenu();

		try {
			command = stoi(ui->gatherInput());
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

			break;

		default:
			//If user enters a string or a invalid number a warning will be displayed
			ui->display("Invalid option!");
			break;
		}
		

		

	}

	return 0;
}
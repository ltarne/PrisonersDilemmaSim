
#include "StrategyGenerator.h"
#include "Tournament.h"
#include "Interpreter.h"

int main() {
	UserInterface* ui = new UserInterface();
	StrategyGenerator strategyGenerator = StrategyGenerator(ui);
	Interpreter interpreter = Interpreter();
	Prisoner* temp;


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
			temp = interpreter.interpretFile("testFile.txt");
			if (temp) {
				ui->display("Strategy file is valid!");
			}
			break;

		default:
			//If user enters a string or a invalid number a warning will be displayed
			ui->display("Invalid option!");
			break;
		}
		

		

	}

	delete ui;
	if (temp) {
		delete temp;
	}

	return 0;
}
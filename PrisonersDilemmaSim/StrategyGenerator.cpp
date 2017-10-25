#include "StrategyGenerator.h"

using namespace std;

StrategyGenerator::StrategyGenerator(UserInterface* ui, Interpreter* interpreter) {
	this->ui = ui;
	this->interpreter = interpreter;
}


StrategyGenerator::~StrategyGenerator() {
}

void StrategyGenerator::writeManualStrategy() {
	ui->display("Enter a file name: ");
	string fileName = ui->gatherString();

	ofstream file(fileName);

	if (!file.is_open()) {
		ui->display("Unable to open file!");
		return;
	}

	string line = "";

	ui->display("Enter EOF to end the file");

	while (line != "EOF") {
		line = ui->gatherString();
		if (line != "EOF") {
			file << line + "\n";
		}
	}

	file.close();
}

void StrategyGenerator::generateStrategies(int n) {
	ui->display("Enter a file name: ");
	string fileName = ui->gatherString();

	vector<string> filePaths = interpreter->generateFileVector(fileName, n);

	for (int i = 0; i < filePaths.size(); ++i) {
		ofstream file(filePaths[i]);

		if (!file.is_open()) {
			ui->display("Unable to open file!");
			return;
		}


		file << "10 IF " << interpreter->getRandomVariable() << " " << interpreter->getRandomComparisonOperator() << " " << interpreter->getRandomVariable() << " GOTO 40\n";
		file << "20 IF " << interpreter->getRandomVariable() << " " << interpreter->getRandomComparisonOperator() << " " << interpreter->getRandomVariable() << " GOTO 50\n";
		file << "30 RANDOM\n";
		file << "40 SILENCE\n";
		file << "50 BETRAY\n";


		file.close();
	}
	
}



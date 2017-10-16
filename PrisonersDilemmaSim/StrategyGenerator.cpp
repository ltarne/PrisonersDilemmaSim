#include "StrategyGenerator.h"

using namespace std;

StrategyGenerator::StrategyGenerator(UserInterface* ui) {
	this->ui = ui;
}


StrategyGenerator::~StrategyGenerator() {
}

void StrategyGenerator::writeManualStrategy() {
	ui->display("Enter a file name: ");
	string fileName = ui->gatherInput();

	ofstream file(fileName);

	if (!file.is_open()) {
		ui->display("Unable to open file!");
		return;
	}

	string line = "";

	ui->display("Enter EOF to end the file");

	while (line != "EOF") {
		line = ui->gatherInput();
		if (line != "EOF") {
			file << line + "\n";
		}
	}

	file.close();
}

void StrategyGenerator::generateStrategies(int n) {

}



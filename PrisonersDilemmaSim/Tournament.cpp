#include "Tournament.h"



Tournament::Tournament(Interpreter * interpreter) {
	this->interpreter = interpreter;
}

Tournament::Tournament(Interpreter* interpreter, string baseName, int n) {
	this->interpreter = interpreter;
	loadPrisoners(interpreter->generateFileVector(baseName, n));
}

Tournament::Tournament(const Tournament &tournament) {
	prisoners = tournament.prisoners;
	interpreter = tournament.interpreter;
}


Tournament::~Tournament() {
	while (prisoners.size()) {
		delete prisoners.back();
		prisoners.pop_back();
	}
}



void Tournament::loadPrisoners(vector<string> filePaths) {
	for (int i = 0; i < filePaths.size(); ++i) {
		prisoners.push_back(interpreter->interpretFile(filePaths[i]));
	}
}

//TODO:Reset variables
void Tournament::executeGame(Prisoner* x, Prisoner* y, int iterations) {
	for (int i = 0; i < iterations; ++i) {
		outcome resultX = interpreter->interpretStrategy(x);
		outcome resultY = interpreter->interpretStrategy(y);

		//TODO: Handle NONE case
		if (resultX == resultY) {
			if (resultX == BETRAY) {
				x->incrementALLOUTCOMES_Z();
				x->incrementMYSCORE(4);
				y->incrementALLOUTCOMES_Z();
				y->incrementMYSCORE(4);
			}
			else {
				x->incrementALLOUTCOMES_W();
				x->incrementMYSCORE(2);
				y->incrementALLOUTCOMES_W();
				y->incrementMYSCORE(2);
			}
		}
		else {
			if (resultX == BETRAY) {
				x->incrementALLOUTCOMES_Y();
				x->incrementMYSCORE(0);
				y->incrementALLOUTCOMES_X();
				y->incrementMYSCORE(5);
			}
			else {
				x->incrementALLOUTCOMES_X();
				x->incrementMYSCORE(5);
				y->incrementALLOUTCOMES_Y();
				y->incrementMYSCORE(0);
			}
		}

		x->incrementITERATIONS();
		y->incrementITERATIONS();
	}
	

	cout << x->getFileName() <<": " << x->getMYSCORE() << y->getFileName() <<  ": " << y->getMYSCORE() << endl;
	
	x->resetVariables();
	y->resetVariables();
}

void Tournament::executeTournament(int iterations) {
	for (int i = 0; i < prisoners.size(); ++i) {
		for (int j = i+1; j < prisoners.size(); ++j) {
			executeGame(prisoners[i], prisoners[j], iterations);
		}
		cout << prisoners[i]->getFileName() << ": " << prisoners[i]->getFinalScore() << endl;
	}
}

void Tournament::resetTournament() {
	while (prisoners.size()) {
		delete prisoners.back();
		prisoners.pop_back();
	}
}

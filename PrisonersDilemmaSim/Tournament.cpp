#include "Tournament.h"



Tournament::Tournament(Interpreter* interpreter, UserInterface* ui) {
	this->interpreter = interpreter;
	this->ui = ui;
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
	while (gangs.size()) {
		delete gangs.back();
		gangs.pop_back();
	}
}



void Tournament::gatherTournamentData(int * n, string * baseName, int * iterations) {
	ui->display("Enter the number of files to be tested: ");
	*n = ui->gatherInteger();
	ui->display("Enter base name for files: ");
	*baseName = ui->gatherString();

	ui->display("Enter number of iterations: ");
	*iterations = ui->gatherInteger();
}

void Tournament::loadPrisoners(vector<string> filePaths) {
	for (int i = 0; i < filePaths.size(); ++i) {
		Prisoner* temp = interpreter->interpretFile(filePaths[i]);
		if (temp) {
			prisoners.push_back(temp);
			results.insert(pair<string, int> (filePaths[i], 0));
		}
		else {
			return;
		}
		
	}
}


void Tournament::loadGangs() {
	if (prisoners.size() == 0) {
		return;
	}

	vector<Prisoner*> temp = prisoners;

	for (int i = 0; i < prisoners.size() / 2; ++i) {
		random_shuffle(temp.begin(), temp.end());
		gangs.push_back(new Gang(vector<Prisoner*>(temp.begin(), temp.end() - temp.size()/2), 10.0f));
		gangs.push_back(new Gang(vector<Prisoner*>(temp.end() - temp.size() / 2, temp.end()), 10.0f));
	}

}

void Tournament::updatePrisoner(Prisoner * prisoner, overallOutcome result) {
	prisoner->setLASTOUTCOME(result);
	switch (result) {
	case W:
		prisoner->incrementALLOUTCOMES_W();
		prisoner->incrementMYSCORE(2);
		break;
	case X:
		prisoner->incrementALLOUTCOMES_X();
		prisoner->incrementMYSCORE(5);
		break;
	case Y:
		prisoner->incrementALLOUTCOMES_Y();
		prisoner->incrementMYSCORE(0);
		break;
	case Z:
		prisoner->incrementALLOUTCOMES_Z();
		prisoner->incrementMYSCORE(4);
		break;
	case A:
		prisoner->incrementALLOUTCOMES_A();
		prisoner->incrementMYSCORE(2.5);
		break;
	case B:
		prisoner->incrementALLOUTCOMES_B();
		prisoner->incrementMYSCORE(3);
		break;
	case C:
		prisoner->incrementALLOUTCOMES_C();
		prisoner->incrementMYSCORE(2);
		break;
	}
}

void Tournament::executeGame(Prisoner* x, Prisoner* y, int iterations) {
	for (int i = 0; i < iterations; ++i) {
		outcome resultX = interpreter->interpretStrategy(x);
		outcome resultY = interpreter->interpretStrategy(y);

		//TODO: Handle NONE case
		if (resultX == resultY) {
			if (resultX == BETRAY) {
				x->incrementALLOUTCOMES_Z();
				x->incrementMYSCORE(4);
				x->setLASTOUTCOME(Z);
				
				y->incrementALLOUTCOMES_Z();
				y->incrementMYSCORE(4);
				y->setLASTOUTCOME(Z);
			}
			else {
				x->incrementALLOUTCOMES_W();
				x->incrementMYSCORE(2);
				x->setLASTOUTCOME(W);

				y->incrementALLOUTCOMES_W();
				y->incrementMYSCORE(2);
				y->setLASTOUTCOME(W);
			}
		}
		else {
			if (resultX == BETRAY) {
				x->incrementALLOUTCOMES_Y();
				x->incrementMYSCORE(0);
				x->setLASTOUTCOME(Y);

				y->incrementALLOUTCOMES_X();
				y->incrementMYSCORE(5);
				y->setLASTOUTCOME(X);
			}
			else {
				x->incrementALLOUTCOMES_X();
				x->incrementMYSCORE(5);
				x->setLASTOUTCOME(X);

				y->incrementALLOUTCOMES_Y();
				y->incrementMYSCORE(0);
				y->setLASTOUTCOME(Y);
			}
		}

		x->incrementITERATIONS();
		y->incrementITERATIONS();
	}
	
	gameResults.insert(pair<string,pair<int,int>>(x->getFileName() + " vs " + y->getFileName(), pair<int,int>(x->getMYSCORE(), y->getMYSCORE())));
	results.find(x->getFileName())->second += x->getMYSCORE();
	results.find(y->getFileName())->second += y->getMYSCORE();
	
	x->resetVariables();
	y->resetVariables();
}

void Tournament::executeGangGame(Gang* xGang, Gang* yGang, int iterations) {
	for (int j = 0; j < iterations; ++j) {
		vector<outcome> xOutcomes;
		vector<outcome> yOutcomes;
		bool xSpy = xGang->isSpyInPlay();

		if (xSpy) {
			ui->displaySpy();
			xGang->chooseSpyAndLeader();
		}

		bool ySpy = yGang->isSpyInPlay();
		if (ySpy) {
			ui->displaySpy();
			yGang->chooseSpyAndLeader();
		}
		
		outcome yOverall;
		for (int i = 0; i < xGang->getStrategies().size(); ++i) {
			if (!(xSpy && xGang->getNextStrategy() == xGang->getSpy())) {
				xOutcomes.push_back(interpreter->interpretStrategy(xGang));
			}
			if (!(ySpy && yGang->getNextStrategy() == yGang->getSpy())) {
				yOutcomes.push_back(interpreter->interpretStrategy(yGang));
			}
			
		}

		int xSilent = count(xOutcomes.begin(), xOutcomes.end(), SILENCE);
		int xBetray = count(xOutcomes.begin(), xOutcomes.end(), BETRAY);

		//TODO: Turn into function
		if (xSpy) {
			if (xSilent < xBetray) {
				xSilent++;
			}
			else if (xSilent < xBetray) {
				xBetray++;
			}
			else {
				if (rand() % 2) {
					xSilent++;
				}
				else {
					xBetray++;
				}
			}
		}

		


		int ySilent = count(yOutcomes.begin(), yOutcomes.end(), SILENCE);
		int yBetray = count(yOutcomes.begin(), yOutcomes.end(), BETRAY);

		if (ySpy) {
			if (ySilent < yBetray) {
				ySilent++;
			}
			else if (xSilent < xBetray) {
				yBetray++;
			}
			else {
				if (rand() % 2) {
					xSilent++;
				}
				else {
					xBetray++;
				}
			}
		}

		bool xSpyFound = xGang->findSpy();
		bool ySpyFound = yGang->findSpy();

		if (xSpyFound && ySpyFound) {
			xGang->incrementMYSCORE(6);
			yGang->incrementMYSCORE(6);
		}
		else if (xSpyFound) {
			ui->displaySpy();
			if (xGang->didLeaderSwap()) {
				xGang->incrementMYSCORE(2);
			}
			else {
				xGang->incrementMYSCORE(0);
			}
		}
		else if (ySpyFound) {
			ui->displaySpy();
			if (yGang->didLeaderSwap()) {
				yGang->incrementMYSCORE(2);
			}
			else {
				yGang->incrementMYSCORE(0);
			}
		}

		if (xSilent == 0 && ySilent == 0) {
			updatePrisoner(xGang, Z);
			updatePrisoner(yGang, Z);
		}
		else if (xBetray == 0 && yBetray == 0) {
			updatePrisoner(xGang, W);
			updatePrisoner(yGang, W);
		}
		else if (xSilent == 0 && yBetray == 0) {
			updatePrisoner(xGang, Y);
			updatePrisoner(yGang, X);
		}
		else if (xBetray == 0 && ySilent == 0) {
			updatePrisoner(xGang, X);
			updatePrisoner(yGang, Y);
		}
		else if ((xSilent > xBetray && ySilent > yBetray) ||
			(xBetray > xSilent && yBetray > ySilent)) {
			updatePrisoner(xGang, C);
			updatePrisoner(yGang, C);
		}
		else if (xSilent > xBetray && ySilent < yBetray) {
			updatePrisoner(xGang, B);
			updatePrisoner(yGang, A);
		}
		else if (xSilent < xBetray && ySilent > yBetray) {
			updatePrisoner(xGang, A);
			updatePrisoner(yGang, B);
		}
		
		
	}

	gameResults.insert(pair<string, pair<int, int>>(xGang->getFileName() + " vs " + yGang->getFileName(), pair<int, int>(xGang->getMYSCORE(), yGang->getMYSCORE())));
	//results.find(xGang->getFileName())->second += xGang->getMYSCORE();
	//results.find(yGang->getFileName())->second += yGang->getMYSCORE();

	xGang->resetVariables();
	yGang->resetVariables();
	

}

void Tournament::compareAllPrisoners(int iterations) {
	for (int i = 0; i < prisoners.size(); ++i) {
		for (int j = i + 1; j < prisoners.size(); ++j) {
			executeGame(prisoners[i], prisoners[j], iterations);
		}
	}
}

void Tournament::compareAllGangs(int iterations) {

	for (int i = 0; i < gangs.size(); ++i) {
		for (int j = i + 1; j < prisoners.size(); ++j) {
			executeGangGame(gangs[i], gangs[j], iterations);
		}
	}
}


void Tournament::executeTournament() {
	string baseName;
	int n = 0;
	int iterations = 0;

	gatherTournamentData(&n, &baseName, &iterations);

	loadTournament(baseName, n);
	if (prisoners.size() < n) {
		ui->display("Tournament load error!");
		return;
	}
	ui->display("Tournament loaded...");
	compareAllPrisoners(iterations);

	ui->display("Would you like to see the detailed results? y/n");
	string detail = "";
	while (detail != "y" && detail != "n") {
		detail = ui->gatherString();
	}
	if (detail == "y") {
		displayResults(true);
	}
	else {
		displayResults(false);
	}
	

	resetTournament();
}

void Tournament::executeGangTournament() {
	string baseName;
	int n = 0;
	int iterations = 0;

	gatherTournamentData(&n, &baseName, &iterations);

	loadTournament(baseName, n);

	loadGangs();
	ui->display("Tournament loaded...");
	compareAllGangs(iterations);

	ui->display("Would you like to see the detailed results? y/n");
	string detail = "";
	while (detail != "y" && detail != "n") {
		detail = ui->gatherString();
	}
	if (detail == "y") {
		displayResults(true);
	}
	else {
		displayResults(false);
	}

	resetTournament();
}

void Tournament::displayResults(bool detail) {
	if (detail) {
		ui->displayDivider();
		ui->display("Displaying Game by game detail");

		for (map<string, pair<int, int>>::iterator i = gameResults.begin(); i != gameResults.end(); ++i) {
			ui->display(i->first + ": " + to_string(i->second.first) + " vs " + to_string(i->second.second));
		}
	}
	ui->displayDivider();
	ui->display("Displaying final results");
	for (map<string, int>::iterator i = results.begin(); i != results.end(); ++i) {
		ui->display(i->first + ": " + to_string(i->second));
		
	}
}

void Tournament::resetTournament() {
	while (prisoners.size()) {
		delete prisoners.back();
		prisoners.pop_back();
	}
	while (gangs.size()) {
		delete gangs.back();
		gangs.pop_back();
	}
	results.clear();
	gameResults.clear();
}

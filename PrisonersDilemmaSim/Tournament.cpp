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
			results.insert(pair<string, vector<int>>(filePaths[i], vector<int>()));
		}
		else {
			return;
		}
		
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
	
	results.find(x->getFileName())->second.push_back(x->getMYSCORE());
	results.find(y->getFileName())->second.push_back(y->getMYSCORE());

	//cout << x->getFileName() <<": " << x->getMYSCORE() << y->getFileName() <<  ": " << y->getMYSCORE() << endl;
	
	x->resetVariables();
	y->resetVariables();
}

void Tournament::executeGangGame(vector<Prisoner*> xGang, vector<Prisoner*> yGang, int iterations) {
	for (int j = 0; j < iterations; ++j) {
		vector<outcome> xOutcomes;
		vector<outcome> yOutcomes;
		
		outcome yOverall;
		for (int i = 0; i < xGang.size(); ++i) {
			xOutcomes.push_back(interpreter->interpretStrategy(xGang[i]));
			yOutcomes.push_back(interpreter->interpretStrategy(yGang[i]));
		}

		int xSilent = count(xOutcomes.begin(), xOutcomes.end(), SILENCE);
		int xBetray = count(xOutcomes.begin(), xOutcomes.end(), BETRAY);


		int ySilent = count(yOutcomes.begin(), yOutcomes.end(), SILENCE);
		int yBetray = count(yOutcomes.begin(), yOutcomes.end(), BETRAY);



		
		
	}
	

}

void Tournament::compareAllPrisoners(int iterations) {
	for (int i = 0; i < prisoners.size(); ++i) {
		for (int j = i + 1; j < prisoners.size(); ++j) {
			executeGame(prisoners[i], prisoners[j], iterations);
		}
		cout << prisoners[i]->getFileName() << ": " << prisoners[i]->getFinalScore() << endl;
	}
}

void Tournament::compareAllGangs(int iterations) {
	executeGangGame(vector<Prisoner*>(&prisoners[0], &prisoners[(prisoners.size() - 1) / 2]), vector<Prisoner*>(&prisoners[prisoners.size() / 2], &prisoners[prisoners.size()-1]), iterations);
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
	//TODO: Fix results rolling over

	displayResults();

	resetTournament();
}

void Tournament::executeGangTournament() {
	string baseName;
	int n = 0;
	int iterations = 0;

	gatherTournamentData(&n, &baseName, &iterations);

	loadTournament(baseName, n);

	compareAllGangs(iterations);



	resetTournament();
}

void Tournament::displayResults() {

}

void Tournament::resetTournament() {
	while (prisoners.size()) {
		delete prisoners.back();
		prisoners.pop_back();
	}
}

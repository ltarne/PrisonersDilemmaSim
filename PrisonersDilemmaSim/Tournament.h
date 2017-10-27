#pragma once
#include <algorithm>
#include <mutex>
#include "Interpreter.h"
#include "Report.h"

class Tournament
{
public:
	Tournament(Interpreter* interpreter, UserInterface* ui);
	Tournament(Interpreter* interpreter, string baseName, int n);
	Tournament(const Tournament &tournament);
	~Tournament();

	inline void loadTournament(string baseName, int n) {
		loadPrisoners(interpreter->generateFileVector(baseName, n));
	}

	void gatherTournamentData(int* n, string* baseName, int* iterations);

	vector<string> prisonersToFileNames(vector<Prisoner*> prisonerList);

	void loadPrisoners(vector<string> filePaths);

	void loadGangs();

	void updatePrisoner(Prisoner* prisoner, overallOutcome result);

	void executeGame(Prisoner* x, Prisoner* y, int iterations);

	void executeGangGame(Gang* xGang, Gang* yGang, int iterations);

	void compareAllPrisoners(int iterations);

	void compareAllGangs(int iterations);

	void executeTournament();

	void executeGangTournament();

	void displayResults(bool detail);


	void resetTournament();

protected:
	Interpreter* interpreter;
	UserInterface* ui;

	vector<Prisoner*> prisoners;
	vector<Gang*> gangs;

	map<string, Report<unsigned int>> reports;


};


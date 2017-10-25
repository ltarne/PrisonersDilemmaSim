#pragma once
#include "Interpreter.h"

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

	void loadPrisoners(vector<string> filePaths);

	void executeGame(Prisoner* x, Prisoner* y, int iterations);

	void compareAllPrisoners(int iterations);

	void executeTournament();

	void displayResults();


	void resetTournament();

protected:
	vector<Prisoner*> prisoners;
	Interpreter* interpreter;
	UserInterface* ui;
	map<string, vector<int>> results;



};


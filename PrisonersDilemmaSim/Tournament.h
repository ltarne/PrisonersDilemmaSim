/* Loads prisoners and compares them
* Author: Luke Burton 140274882
* Date: 27/10/2017
*/
#pragma once
#include <algorithm>
#include <mutex>
#include <thread>
#include "Interpreter.h"
#include "Report.h"

struct threadLock {
	vector<Prisoner*>* prisoners;
	mutex mut;
};

class Tournament
{
public:
	Tournament(Interpreter* interpreter, UserInterface* ui);
	Tournament(Interpreter* interpreter, string baseName, int n);
	Tournament(const Tournament &tournament);
	~Tournament();

	/*Main setup for tournaments where prisoners are loaded 
	* baseName: File base name
	* n: Number of files
	*/
	inline void loadTournament(string baseName, int n) {
		loadPrisoners(interpreter->generateFileVector(baseName, n));
	}

	/*Gather tournament preliminary data*/
	void gatherTournamentData(int* n, string* baseName, int* iterations);

	/*Return a vector of file names from a vector of prisoners*/
	vector<string> prisonersToFileNames(vector<Prisoner*> prisonerList);

	/*Load all prisoners*/
	void loadPrisoners(vector<string> filePaths);

	/*Load all gangs*/
	void loadGangs();

	/*Update a prisoners variables*/
	void updatePrisoner(Prisoner* prisoner, overallOutcome result);

	/*Execute a single prisoner match up*/
	void executeGame(Prisoner* x, Prisoner* y, int iterations);

	/*Execute a single gang match up*/
	void executeGangGame(Gang* xGang, Gang* yGang, int iterations);

	/*Matches up all prisoners against each other*/
	void compareAllPrisoners(int iterations);

	/*Matches up all gangs agains each other*/
	void compareAllGangs(int iterations);

	/*Runs a prisoner only tournament*/
	void executeTournament();

	/*Runs a full gang tournament*/
	void executeGangTournament();

	/*Display tournament results*/
	void displayResults();

	/*Clears tournament*/
	void resetTournament();

protected:
	Interpreter* interpreter;
	UserInterface* ui;

	vector<Prisoner*> prisoners;
	vector<Gang*> gangs;

	map<string, Report<unsigned int>> reports;


};


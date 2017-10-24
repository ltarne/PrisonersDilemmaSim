#pragma once
#include "Prisoner.h"
#include "Interpreter.h"

class Tournament
{
public:
	Tournament(Interpreter* interpreter);
	Tournament(Interpreter* interpreter, string baseName, int n);
	Tournament(const Tournament &tournament);
	~Tournament();

	inline void loadTournament(string baseName, int n) {
		loadPrisoners(interpreter->generateFileVector(baseName, n));
	}

	

	void loadPrisoners(vector<string> filePaths);

	void executeGame(Prisoner* x, Prisoner* y, int iterations);

	void executeTournament(int iterations);


	void resetTournament();

protected:
	vector<Prisoner*> prisoners;
	Interpreter* interpreter;


};


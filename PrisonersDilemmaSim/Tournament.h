#pragma once
#include "Prisoner.h"
#include "Interpreter.h"

class Tournament
{
public:
	Tournament(Interpreter* interpreter);
	~Tournament();

	void loadPrisoners(vector<string> filePaths);

	void executeGame(Prisoner* x, Prisoner* y);

	void executeTournament();

protected:
	vector<Prisoner*> prisoners;
	Interpreter* interpreter;

};


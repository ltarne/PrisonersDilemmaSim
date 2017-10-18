#pragma once
#include <map>
#include <vector>

using namespace std;

class Prisoner
{
public:
	Prisoner(map<string, vector<string>> strategy);
	~Prisoner();

	inline map<string, vector<string>> getStrategy() {
		return strategy;
	}

	inline void setStrategy(map<string, vector<string>> strategy) {
		this->strategy = strategy;
	}


protected:

	map<string, vector<string>> strategy;

	unsigned int LASTOUTCOME;
	unsigned int ALLOUTCOMES_W;
	unsigned int ALLOUTCOMES_X;
	unsigned int ALLOUTCOMES_Y;
	unsigned int ALLOUTCOMES_Z;
	unsigned int ITERATIONS;
	unsigned int MYSCORE;
};


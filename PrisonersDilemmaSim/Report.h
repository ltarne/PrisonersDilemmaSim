#pragma once
#include <string>
#include <vector>

using namespace std;

template <class T>
class Report
{
public:

	Report(string name) {
		this->name = name;
		finalResult = 0.0f;
	}
	Report(string name, vector<string> memberNames) {
		this->name = name;
		this->memberNames = memberNames;
		finalResult = 0.0f;
	}
	~Report() {}

	inline void insertResult(float result) {
		this->result.push_back( result);
		finalResult += result;
	}

	inline void insertGameOutcomes(string name, vector<T> gameResult) {
		gameOutcomes.push_back(pair<string, vector<T>>(name, gameResult));
	}

	inline void insertSpyResult(string name, vector<bool> spyVariable) {
		spyVariables.insert(name, spyVariable);
	}
	

	inline string getName() {
		return name;
	}

	inline vector<string> getMemberNames() {
		return memberNames;
	}

	inline float getFinalResult() {
		return finalResult;
	}

	inline vector<pair<string, vector<T>>>  getGameOutcomes() {
		return gameOutcomes;
	}




protected:
	string name;
	vector<string> memberNames;

	float finalResult;
	vector<float> result;
	vector<pair<string, vector<T>>> gameOutcomes;

	vector<pair<string, vector<bool>>> spyVariables;
};


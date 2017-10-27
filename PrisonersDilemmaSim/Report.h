/* Holds data used for printing reports
* Author: Luke Burton 140274882
* Date: 27/10/2017
*/
#pragma once
#include <string>
#include <vector>
#include <fstream>
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

	/*Ostream operator overload (Sorry was a bit rushed!)*/
	friend ostream& operator<<(ostream& os, Report<unsigned int>& report) {
		string memberNames = "";
		string gameOutcomes = "";
		for (int i = 0; i < report.memberNames.size(); ++i) {
			memberNames.append(report.memberNames[i] + "\n");
		}
		for (int i = 0; i < report.gameOutcomes.size(); ++i) {
			gameOutcomes.append(to_string((int)report.gameOutcomes[i].second[0]) + "\n");
		}
		if (report.spyVariables.size() != 0) {
			string spyVariables = "";
			for (int i = 0; i < report.spyVariables.size(); ++i) {
				spyVariables.append(to_string((int)report.spyVariables[i].second.first) + "\n");
			}
			
			
			os << report.name << "\n" << memberNames  << "\n---------------\n" << gameOutcomes << "\n" << spyVariables<< "\n---------------\n";
		}
		else {
			os << report.name << "\n" << memberNames << "\n---------------\n" << gameOutcomes << "\n---------------\n";
		}

		return os;
		
	}

	/*Outputs report to file*/
	void toFile(string filePath) {
		ofstream file;

		file.open(filePath, ofstream::app);

		if (!file.is_open()) {
			return;
		}

		file << *this;

		file.close();

	}

	inline void insertResult(float result) {
		this->result.push_back( result);
		finalResult += result;
	}

	inline void insertGameOutcomes(string name, vector<T> gameResult) {
		gameOutcomes.push_back(pair<string, vector<T>>(name, gameResult));
	}

	inline void insertSpyResult(string name, pair<T, T> spyVariable) {
		spyVariables.push_back(pair<string, pair<T, T>>( name, spyVariable));
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

	inline vector<pair<string, pair<T, T>>> getSpyVariables() {
		return spyVariables;
	}




protected:
	string name;
	vector<string> memberNames;

	float finalResult;
	vector<float> result;
	vector<pair<string, vector<T>>> gameOutcomes;

	vector<pair<string, pair<T, T>>> spyVariables;
};


#include <iostream>
#include <random>
#include <ctime>
#include <unistd.h>
#include <vector>
#include "voter.h"
using namespace std;

Voter frontForWait(vector<Voter> line);
void pushToWait(Voter voter, vector<Voter> &line);
void popFromWait(vector<Voter> line);
void pushToBallot(Voter voter, vector<Voter> line, int lineNumber);
int popFromBallot(vector<Voter> line, int lineNumber);

int main(int argc, char *argv[])
{
	default_random_engine generator(time(0));
	srand(time(0));
	int minutes = atoi(argv[1]);
	int avgPeoplePerMinute = atoi(argv[2]);
	int avgTimeToVote = atoi(argv[3]);
	int numVotingQueues = atoi(argv[4]);
	int verbose = atoi(argv[5]);
	int clock = 0;
	int pickName = 0;
	int shortestLine = 0;
	int totalNumOfVotersProcessed = 0;
	int processTime = 0;
	int totalProcessTime = 0;
	int maxProcessTime = 0;
	double mean = 0;
	vector<Voter> waitLine;
	vector<Voter> VoteQueues[numVotingQueues];

	string names[10] = {"Ethan", "Eli", "Ben", "Alex", "Martin", "Rebekah", "Tori", "Zach", "Chandler", "Evan"};
	string name;

	for(int i = 0; i < minutes; i++)
	{
		if(verbose)
			cout << "Minute " << i << endl;

		cout << "______________________" << endl;
		normal_distribution<double> numArrival(avgPeoplePerMinute, 1);
		int numVoters = numArrival(generator);

		if(numVoters < 0)
			numVoters = 0;

		for(int j = 0; j < numVoters; j++)
		{
			int pickName = rand() % 10;
			name = names[pickName];

			Voter person(name, 0);
			pushToWait(person, waitLine);
		}

		for(int k = 0; k < waitLine.size(); k++)
			waitLine[k].updateWait();

	}
	return 0;
}

Voter frontForWait(vector<Voter> line)
{
	return *line.begin();
}

void pushToWait(Voter voter, vector<Voter> &line)
{
	line.push_back(voter);
	cout << voter.getName() << " has entered the wait line" << endl;
}

void popFromWait(vector<Voter> line)
{
	Voter temp = frontForWait(line);
	cout << temp.getName() << " has left the wait line" << endl;
	line.erase(line.begin());
}


void pushToBallot(Voter voter, vector<Voter> line, int lineNumber)
{
	line.push_back(voter);
	cout << voter.getName() << " has entered ballot queue #" << lineNumber << endl;
}

int popFromBallot(vector<Voter> line, int lineNumber)
{
	int grabTime = 0;
	Voter temp = frontForWait(line);
	grabTime = temp.getWait();
	cout << temp.getName() << " has left ballot queue #" << lineNumber << " with a total wait time of " << grabTime << endl;
	line.erase(line.begin());
	return grabTime;
}






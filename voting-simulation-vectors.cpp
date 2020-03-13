#include <iostream>
#include <random>
#include <ctime>
#include <unistd.h>
#include <vector>
#include "voter.h"
using namespace std;

Voter frontForWait(vector<Voter> line);
void pushToWait(Voter voter, vector<Voter> &line);
Voter popFromWait(vector<Voter> &line);
void pushToBallot(Voter voter, vector<Voter> &line, int lineNumber);
int popFromBallot(vector<Voter> &line, int lineNumber);

int main(int argc, char *argv[])
{
	default_random_engine generator(time(0));
	srand(time(0));
	int minutes = atoi(argv[1]);
	int avgPeoplePerMinute = atoi(argv[2]);
//	int avgTimeToVote = atoi(argv[3]);
	int numVotingQueues = atoi(argv[3]);
	int verbose = atoi(argv[4]);
	int clock = 0;
	int pickName = 0;
	int shortestLine = 0;
	int totalNumOfVotersProcessed = 0;
	int processTime = 0;
	int totalProcessTime = 0;
//	int maxProcessTime = 0;
	double mean = 0;
	int position = 0;
	vector<Voter> waitLine;
	vector<Voter> VoteQueues[numVotingQueues];

	string names[10] = {"Ethan", "Eli", "Ben", "Alex", "Martin", "Rebekah", "Tori", "Zach", "Chandler", "Evan"};
	string name;

	for(int i = 0; i < minutes; i++)
	{
		if(verbose)
		{
			cout << endl;
			cout << "Minute " << i << endl;
		}
		if(!waitLine.empty())
		{
			Voter temp = popFromWait(waitLine);
			//int position = 0;

			if(position < 4)
			{
				pushToBallot(temp, VoteQueues[position], position);
				position++;
			}
			else
			{
				position = 0;
				pushToBallot(temp, VoteQueues[position], position);
				position++;
			}
		}

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


		if(VoteQueues[numVotingQueues].empty())
		{
			for(int l = 0; l < 4; l++)
			{
				if((VoteQueues[l][0].getWait() - minutes) % 2 == 0)
				{
					totalNumOfVotersProcessed++;
					processTime = popFromBallot(VoteQueues[l], l);
				}		
				for(int m = 0; m < VoteQueues[l].size(); m++)
				{
					VoteQueues[l][m].updateWait();
				}
			}		

		}
		
		totalProcessTime += processTime;
		

	}
	
	mean = 1.0*(processTime / totalNumOfVotersProcessed);
	cout << mean << endl;

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

Voter popFromWait(vector<Voter> &line)
{
	Voter temp = frontForWait(line);
	cout << temp.getName() << " has left the wait line" << endl;
	line.erase(line.begin());
	return temp;
}


void pushToBallot(Voter voter, vector<Voter> &line, int lineNumber)
{
	line.push_back(voter);
	cout << voter.getName() << " has entered ballot queue #" << lineNumber << endl;
}

int popFromBallot(vector<Voter> &line, int lineNumber)
{
	int grabTime = 0;
	Voter temp = frontForWait(line);
	grabTime = temp.getWait();
	cout << temp.getName() << " has left ballot queue #" << lineNumber << " with a total wait time of " << grabTime << endl;
	line.erase(line.begin());
	return grabTime;
}



#include "voter.h"
#include <iostream>

using namespace std;

Voter::Voter(string inName, int inWait)
{
	name = inName;
	waitTime = inWait;
}

Voter::Voter()
{
	name = "";
	waitTime = 0;
}

void Voter::updateWait()
{
	waitTime++;
}

string Voter::getName() const
{
	return name;
}

int Voter::getWait() const
{
	return waitTime;
}
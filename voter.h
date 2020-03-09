#include <iostream>
#include <string>
using namespace std;

class Voter
{
	private:
		string name;
		int waitTime;
	public:
		Voter(string, int);
		Voter();

		void updateWait();

		string getName() const;
		int getWait() const;
};
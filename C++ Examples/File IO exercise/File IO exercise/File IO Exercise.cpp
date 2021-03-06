// Sean Carlson Data Structures IC 8.1.cpp : Defines the entry point for the console application.
//

/*
By Sean Carlson
This is an in-class exercise from week 8 of Data Strctures when I was at Becker College.
*/
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	ifstream fin;
	ofstream fout;
	fin.open("InputFile.txt");
	fout.open("OutputFile.txt");
	string customer;
	queue<string> customers;
	vector<string> problems;

	problems.push_back("game does not start");
	problems.push_back("game crashes");
	problems.push_back("game hangs");

	while (!fin.eof())
	{
		getline(fin, customer);
		customers.push(customer);
	}

	for (unsigned int i=0; i<customers.size(); i++)
	{
		int index = rand() % problems.size();
		string rand_problem;
		rand_problem = problems[i];

		fout << customers.front() << rand_problem << endl;
		customers.pop();
	}
	fout.close();
	fin.close();








    return 0;
}


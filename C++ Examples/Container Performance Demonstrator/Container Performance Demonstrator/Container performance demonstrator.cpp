#include "stdafx.h"
#include <iostream>

#include <cstdlib>

#include<vector>
#include <iterator>
#include <set>
#include <unordered_set>

#include <algorithm>
#include <ctime>
#include <random>
#include <chrono>

#include <thread>



using namespace std;

void fillVector(vector<int> vector1mil);/* Requests 100,000,000 size for 100 million random integers. Records the time it takes to fill. Also confirms results of operations in cout.*/
void fillset(set<int> set1mil);	//Fills a set with 100 million rand ints.Same as before only it doesn't preallocate space.
void filluset(unordered_set<int> unorderedset1mil);//Obviously does the same thing.

int main()
{
	vector<int> vector1mil;
	set<int> set1mil;
	unordered_set<int> unorderedset1mil;

	srand(time(NULL));
	

	/*Executing fill operations concurrently. The functions pause on completion and wait for the other functions to be caught up before proceeding to searching.*/
	thread first(fillVector, vector1mil);
	thread second(fillset, set1mil);
	thread third(filluset, unorderedset1mil);

	first.join();
	second.join();
	third.join();
	





	//Searching vector
	vector<int>::iterator iter;
	cout << "Checking vector for the number 250...\n\n";
	auto start = chrono::steady_clock::now();

	iter = find(vector1mil.begin(), vector1mil.end(), 250);
	if (iter != vector1mil.end())
		cout << "Element found: " << *iter << endl;
	else
		cout << "Element not found." << endl;

	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds : "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;

	//search complete


		//Sorting vector
	sort(vector1mil.begin(), vector1mil.end());

	start = chrono::steady_clock::now();
	//Searching sorted vector.
	cout << "looking for a 9... \n";
	if (binary_search(vector1mil.begin(), vector1mil.end(), 9))
		cout << "found!\n"; else std::cout << "not found.\n";

	end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds : "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;
	//search complete

		//Vector no longer needed.
	vector1mil.clear();
	cout << "Vector cleared.";
	vector1mil.~vector();
	cout << "Vector Destructor called.\n";




	set<int>::iterator siter;// set iterator
	cout << "Checking set for the number 25...\n\n";
	start = chrono::steady_clock::now();
	//Searching set
	siter = find(set1mil.begin(), set1mil.end(), 25);
	if (siter != set1mil.end())
		cout << "Element found: " << *siter << endl;
	else
		cout << "Element not found." << endl;

	end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds : "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;
	//Search complete
	set1mil.~set();
	cout << "Set destructor called\n";






	unordered_set<int>::iterator usiter;// u_set iterator
	cout << "Checking unordered set for the number 253...\n\n";
	start = chrono::steady_clock::now();



	//Searching unordered set
	usiter = find(unorderedset1mil.begin(), unorderedset1mil.end(), 253);
	if (usiter != unorderedset1mil.end())
		cout << "Element found: " << *usiter << endl;
	else
		cout << "Element not found." << endl;

	end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds : "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;
	//Search complete
	unorderedset1mil.~unordered_set();
	cout << "U_set destructor called.\n";


	
	int wait;
	cin >> wait;
	return 0;
}

void fillVector(vector<int> vector1mil)
{

	/*
	Fills a vector.


	Requests 100,000,000 size for 100 million random integers.
	Records the time it takes to fill.
	Also confirms results of operations in cout.
	*/
	const unsigned int limit = 100000000;
	vector1mil.reserve(100000000);
	cout << "filling vector with 100 million random numbers\n";
	auto start = chrono::steady_clock::now();
	for (int i = 0; i < limit; i++)
	{
		vector1mil.push_back(rand());
	}
	cout << "Vector filled.\n" << "Vector size is now:" << vector1mil.size() << endl;
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in minutes : "
		<< chrono::duration_cast<chrono::minutes>(end - start).count()
		<< " minutes" << endl;
}

void fillset(set<int> set1mil)
{

	/*
	Fills a set with 100 million rand ints. Same as before only it doesn't preallocate space.
	*/
	const unsigned int slimit = 10000000;
	cout << "Filling set with 10 million random numbers\n";
	auto start = chrono::steady_clock::now();
	for (int i = 0; i < slimit; i++)
	{
		set1mil.insert(rand());
	}
	cout << "Set filled.\n\n";
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in seconds : "
		<< chrono::duration_cast<chrono::seconds>(end - start).count()
		<< " seconds" << endl;
}

void filluset(unordered_set<int> unorderedset1mil)
{


	const unsigned int uslimit = 10000000;
	auto start = chrono::steady_clock::now();
	cout << "Filling unordered set with 10 million random numbers\n";
	for (int i = 0; i < uslimit; i++)
	{
		
		unorderedset1mil.insert(rand());
		
	}
	cout << "Unordered sets filled \n";
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in seconds : "
		<< chrono::duration_cast<chrono::seconds>(end - start).count()
		<< " seconds" << endl;
}



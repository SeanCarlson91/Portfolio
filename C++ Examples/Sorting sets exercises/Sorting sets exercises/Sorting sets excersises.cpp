
//Containers
#include <vector>
#include <set>
#include <unordered_set>


//Misc tools.
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>


using namespace std;

void fillVector(vector<int> init_element_holder, int limit);
void fillUset(unordered_set<int> unique_elements, vector<int> init_element_holder);
void fillSet(set<int> sorted_element_holder, vector<int> init_element_holder);
int main()
{
	srand(time(NULL));

	/*
	Part 1. Write a program doing the following: given a vector of (possibly repeating) integers, create an unordered set of unique elements (elements of the vector without repetition) and output them.

Use the following algorithm: for every element of the original vector check if it contains in unique_elements, if not - add it to unique_elements.

if (unique_elements.find(vec[i])==unique_elements.end()) //vec[i] is not inside unique_elements

    unique_elements.insert(vec[i]);
	*/
	vector<int> init_element_holder;// Initital number holder - holds numbers after being random generated. To be sorted into unique_numbers later.
	unordered_set<int> unique_elements;
	set<int> sorted_element_holder;
	
	const unsigned int limit = 100000;


	fillVector(init_element_holder, limit);

	fillUset(unique_elements, init_element_holder);

	
	/*
	Part 2. How should we change the program to store unique_elements in sorted order? Test it: see if you get sorted output.
	*/
	
	fillSet(sorted_element_holder, init_element_holder);

	
	/*
	Part 3. Compare the time that it would take to implement the algorithm (without the output) for a 
	big vector (of 100,000 elements - random integers from 0 to 100), 
	declaring unique_elements: a) vector b) set c) unordered_set.

	Notice how to call find and add for unique_elements declared as a vector: 
	find(unique_elements.begin(), unique_elements.end(), x); unique_elements.push_back(x);
	*/

	




	int wait;
	cin >> wait;
	return 0;
}




void fillVector(vector<int> init_element_holder, int limit)
{
	auto start = chrono::steady_clock::now();
	cout << "Clock Started: filling.";

	for (int i = 0; i <= limit; i++)
	{
		init_element_holder.push_back(rand());
	}
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds : "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;
}




void fillUset(unordered_set<int> unique_elements, vector<int> init_element_holder)
{
	auto start = chrono::steady_clock::now();
	cout << "Clock Started: filling.";
	for (int i = 0; i <= init_element_holder.size() - 1; i++)
	{
		if (unique_elements.find(init_element_holder[i]) == unique_elements.end()) //vec[i] is not inside unique_elements

			unique_elements.insert(init_element_holder[i]);
	}
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds : "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;
}



void fillSet(set<int> sorted_element_holder, vector<int> init_element_holder)
{
	auto start = chrono::steady_clock::now();
	cout << "Clock Started: filling.";
	for (int i = 0; i <= init_element_holder.size() - 1; i++)
	{
		if (sorted_element_holder.find(init_element_holder[i]) == sorted_element_holder.end()) //vec[i] is not inside unique_elements
		{
			sorted_element_holder.insert(init_element_holder[i]);
		}
	}
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds : "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;
	/*
	//Turn this on if you want to see 10,000 lines of sorted numbers from 0-10,000;
	set<int>::iterator it;
	for (it = sorted_element_holder.begin(); it != sorted_element_holder.end(); it++)
	{
		cout << *it << endl;
	}
	*/
}

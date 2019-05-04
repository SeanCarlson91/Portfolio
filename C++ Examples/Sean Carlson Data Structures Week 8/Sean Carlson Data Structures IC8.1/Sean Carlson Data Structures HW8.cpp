
/*
By Sean Carlson
This is homework from week 8 of Data Strctures when I was at Becker College.
It's a simulation of an airport take off and landing sequence using queues.
*/

#include <queue>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include<thread>



using namespace std;


class airplane
{
public:
	
	airplane(int tailNumber);
	~airplane();

	
	int gettailNumber();
private:
	int m_tailNumber;


};


class runway
{
public:
	runway(bool status);

	bool getstatus();
	void setstatus(bool status);
	
//	void OutputTOLs(short unsigned int landings, short unsigned int takeoffs);//Outputs take offs and landings.
	bool status;
private:
	bool m_status;
//	short unsigned int landings, takeoffs;
	
};

void Queuepopper(queue<int>& arrivals, queue<int>& departures);

int main()
{

	float arrivalprob;
	float departureprob;
	runway runway(true);
	airplane plane();
	queue<airplane> arrivals;
	queue<airplane> departures;



	cout << "Input arrival probability: ";
	cin >> arrivalprob;
	while (arrivalprob>1 || arrivalprob<0)
	{
		cout << "Invalid input ";
		cout << "Input arrival probability: ";
		cin >> arrivalprob;

	}
	cout << "Input departure probability: ";
	cin >> departureprob;
	while (departureprob>1 || departureprob<0)
	{
		cout << "Invalid input ";
		cout << "Input departure probability: ";
		cin >> departureprob;

	}

	
	cout << "Input duration of simulation in seconds: ";
	int duration;
	cin >> duration;


	for (int i = 0; i < duration; i++)
	{
		
		runway.status=true;
		srand(time(NULL));
		
		float randomDep = rand() / float(RAND_MAX);
		if (randomDep <= departureprob)//Generates a plane for the departue queue with a random 3 digit tail number requesting permission for take off.
		{
			
			airplane plane(rand() % 999);
			departures.push(plane);
			cout << "ATC this is " << departures.back().gettailNumber() << " requesting departure clearance." << endl;
		}


		float randomArv = rand() / float(RAND_MAX);
		if(randomArv<=arrivalprob)//Generates a plane for the arrival cue with a random 3 digit tail number requesting to land.
		{
			
			airplane plane(rand()%999);
			arrivals.push(plane);
			cout << "ATC this is " << arrivals.back().gettailNumber() <<  " requesting permission to land. Approach button 15. Angels .5. Over." << endl;
		}


		cout << endl;
		cout << "Arrivals: " << arrivals.size() << endl;
		cout << "Departures: " << departures.size()<<endl << endl;





		//landing/departure sequence
		if (arrivals.size() > 0)//If the runway has more than 0 planes on it it's occupied
		{
			runway.setstatus(false);
		//	cout << "Runway status false\n\n\n";
			if (runway.getstatus() == false)
			{
				cout << "Runway status: Occupied" << endl;
			}
			//cout << "Output expected\n\n";


			cout << arrivals.front().gettailNumber() << " you are cleared for landing on runway 5205. Over."<<endl;
			arrivals.pop();

			runway.setstatus(true);//After the plane lands it's taxiing off the runway so the runway is set to clear.
			if (runway.getstatus() == true)
			{
				cout << "Runway status: Clear" << endl;
			}
		}



		if (arrivals.size()==0 && departures.size()>0)//If there are no planes coming in to land AND a plane is waiting to take off, the runway is set to occupied and the plane is given permission to take off.
		{
			runway.setstatus(false);
			//cout << "Runway status set to false.\n\n\n";
			if (runway.getstatus() == false)
			{
				cout << "Runway status: Occupied" << endl;
			}
			//cout << "Output expected.\n\n\n\n\n\n\n";

	
			cout << departures.front().gettailNumber() << " departure clearance granted on runway 5205. Over." << endl;
			departures.pop();

			runway.setstatus(true);//After take off the runway is set to clear.
			if (runway.getstatus() == true)
			{
				cout << "Runway status: Clear" << endl;
			}
		}
		

		this_thread::sleep_for(chrono::seconds(1));//1 second time delay before loop repeats.
	}//End for loop


	int wait;
	cin >> wait;
	return 0;
}








void Queuepopper(queue<int> & arrivals, queue<int> & departures)
{
	while (!arrivals.empty()||!departures.empty())
	{
		departures.pop();
		arrivals.pop();
	}
}






airplane::airplane(int tailNumber)
{
	m_tailNumber = tailNumber;
}

airplane::~airplane()
{
}

int airplane::gettailNumber()
{
	return m_tailNumber;
}






runway::runway(bool status)
{
	status = true;
}



bool runway::getstatus()
{
	return m_status;
}
void runway::setstatus(bool status)
{
	m_status = status;
}

/*
void runway::OutputTOLs(short unsigned int takeoffs, short unsigned int landings)
{
	cout << "Take offs: " << takeoffs<<endl;
	cout << "Landings: " << landings<<endl;
}
*/

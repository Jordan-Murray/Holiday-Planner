#include "stdafx.h"
#include "Destination.h"
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string>

using namespace std;

Destination::Destination()
{

};

Destination::Destination(string dName, int dRating) //contructor
{
	DestinationName = dName;
	DestinationRating = dRating;
}

int Destination::getRating() // outputs desintaiton name
{
	return DestinationRating;
}

string Destination::getDestinationName()
{
	return DestinationName;
}

void Destination::display() //Displays destination array. As seen in Session 10.
{
	cout << setfill(' ') << setw(10) << DestinationName << setfill(' ') << setw(10) << DestinationRating << "\n" << endl;
}

bool Destination::getDestination(string userInput) //gets user chosen destination
{
	if (userInput == DestinationName)
	{
		cout << "Success!\n" << "You have chosen " << DestinationName << endl;
		return true;
	}
	else
	{
		return false;
	}
}


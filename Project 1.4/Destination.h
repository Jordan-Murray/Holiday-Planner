#pragma once

#include "stdafx.h"
#include <string>


using namespace std;

class Destination //Destination Class
{
public:
	Destination(string dName, int dRating);
	Destination();
	void display();
	bool getDestination(string userInput);
	string getDestinationName();
	int getRating();

private:
	string DestinationName;
	int DestinationRating;
	friend class Hotel; //allows hotel to access private members
};

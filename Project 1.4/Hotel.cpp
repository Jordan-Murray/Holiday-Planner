#include "stdafx.h"
#include "Hotel.h"
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string>

using namespace std;


Hotel::Hotel(string hName, int hPrice) //contructor
{
	HotelName = hName;
	HotelPrice = hPrice;

}

Hotel::Hotel()
{

};

void Hotel::hdisplay() //Displays hotel array
{
	cout << setfill(' ') << setw(10) << HotelName << setfill(' ') << setw(10) << RealPrice << "\n" << endl;
}

void Hotel::setPrice(int realPriceNew)
{
	RealPrice = realPriceNew;
}


bool Hotel::canAfford(int budget, int maxRealPriceNew)
{
	if ((budget > RealPrice) && (budget < maxRealPriceNew))
	{
		cout << "\t" << HotelName << "\n" << endl;

		return false;
	}
	else if (budget > maxRealPriceNew) //needs changing to a variable maxPrice to take into account most expensive destination and duration
	{
		cout << "\t" << HotelName << "\n" << endl;
		return true;
	}

}

string Hotel::getName()
{
	return HotelName;
}

int Hotel::getPrice()
{
	return HotelPrice;
}
int Hotel::getRealPrice()
{
	return RealPrice;
}

int Hotel::getDestinationRating(Destination ratingObject)
{
	return ratingObject.DestinationRating;
}

bool Hotel::getHotel(string userInput, int hotelPrice, int budget) //gets user chosen destination
{
	if ((userInput == HotelName) && (hotelPrice <= budget))
	{
		cout <<"\nYou have chosen to stay at " << HotelName << endl;
		return true;
	}
	else
	{
		return false;
	}
}
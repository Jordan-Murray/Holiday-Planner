#pragma once

#include "stdafx.h"
#include "Destination.h"
#include <string>

using namespace std;

class Hotel//Hotel Class 
{
public:
	Hotel(string hName, int hPrice);
	Hotel();
	void hdisplay();
	bool canAfford(int budget, int maxRealPriceNew);
	string getName();
	int getDestinationRating(Destination DestinationRating);
	int getPrice();
	void setPrice(int realPrice);
	bool getHotel(string userInput, int hotelPrice, int budget);
	int getRealPrice();

private:
	string HotelName;
	int HotelPrice;
	int Budget;
	int RealPrice;

};
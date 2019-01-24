#include "stdafx.h"
#include "Destination.h"
#include "Hotel.h"
#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

//Declaration of functions not uses in classes

int calcPrice(int budget, double rating);
double calcPriceLength(double destLength, int chosenHotelPrice);
double flights(int destRatingNew);
double upgradedFlights(double flights);
void printPackage(string destName, string chosenHotel, double destLength, string upgradedFlightsStr, int total, int budget);
void welcome();

int main()
{
	int i = 0;
	string destName , chosenHotel, upgradedFlightsStr;
	double destLength = 0;
	double price = 0;
	int budget = 0;

	
	ofstream saveFile;
	saveFile.open("saveFile.txt");
	//ifstream saveFile;
	
	
	bool saveHoliday = false;
	
	bool newHoliday = false;
	bool saveHolidayValidInput = false;
	while (newHoliday == false)
	{
		const int numHotels = 5;
		const int numDestinations = 5;
		Destination destinationlist[numDestinations];

		//String to hold destination from file
		string dName;
		//Int to hold rating from file
		int dRating = 0;
		//sets stream to read .txt
		ifstream destFile("destinations.txt");
		if (destFile.is_open())
		{
			for (int i = 0; i < numDestinations; i++)
			{
				//reads in variables
				destFile >> dName;
				destFile >> dRating;
				//adds variables into array at [i]
				destinationlist[i] = { dName , dRating };
			}
		}
		else
		{
			cout << "Your file was not found" << endl;
		}

		Hotel hotellist[numHotels] = { Hotel("Hostel", 200),
			Hotel("Motel",600),
			Hotel("PremierInn",1000),
			Hotel("Hilton",3000),
			Hotel("FourSeasons",7500)
		};

		//Welcome Message

		welcome();

		//Destination

		cout << "These are the possible destinations for your holiday:" << endl;
		cout << "\nDestination    Rating\n" << endl;

		for (int i = 0; i < numDestinations; i++)
		{
			destinationlist[i].display(); //Displaying each destination
		}

		cout << "\n\nPlease type in your chosen destination" << endl;//Prompt
		cout << "Destination :";
		string ChosenDest; //User chosen destination
		cin >> ChosenDest;
		bool Success = false;
		Destination destratingObj;
		Hotel destRatingObj;
		int maxRating = 0;
		while (Success == false)
		{
			for (int i = 0; i < numDestinations; i++) //Displaying each line
			{
				Success = destinationlist[i].getDestination(ChosenDest); //checks valid input
				destName = destinationlist[i].getDestinationName();
				for (int i = 0; i < 3; i++)
				{
					if (maxRating < (destinationlist[i].getRating())) //finds max rating of all destinations
					{
						int y = destinationlist[i].getRating();
						maxRating = y;
					}
				}
				//interating through array
				if (Success == true)									// and checking against user 
				{														//input, using getDestination
					destratingObj = destinationlist[i];
					//breaks as soon as it finds a match
					break;
				}
				else if ((Success == false) && (destName == dName)) //dName will have last destination name in the file
				{														//WHEN LOADING FILE NEEDS TO CHECK LAST DESTINATION
					cout << "Please enter a valid Destination" << endl;
					cin >> ChosenDest;
				}
			}
		}

		int destRating = 0;
		int hotelPrice;
		destRating = destRatingObj.getDestinationRating(destratingObj); //obtaining destination ratin
		int realPrice;

		//Printing Hotels

		cout << "\nHotel		Price\n" << endl;
		for (int i = 0; i < 5; i++)
		{
			hotelPrice = hotellist[i].getPrice();
			realPrice = calcPrice(hotelPrice, destRating);
			hotellist[i].setPrice(realPrice);
			hotellist[i].hdisplay(); //Displaying each hotel
		}

		int maxRealPrice; //realPrice indicates hotels price based on destination
		int maxPrice;

		maxPrice = hotellist[4].getPrice();
		maxRealPrice = calcPrice(maxPrice, destRating);

		//Budget 

		string hotelname;
		double holidayTotal;
		cout << "\nPlease enter your budget for the holiday." << endl;
		cout << "Budget : ";
		cin >> budget;
		while ((budget <= 0) || (budget<hotellist[0].getRealPrice()))
		{
			cout << "Please enter a valid budget" << endl;
			cin >> budget;
		}
		holidayTotal = budget;
		cout << "Your budget is " << budget << endl;

		//Affordable Hotels

		cout << "\nThese are the hotels within your budget!\n" << endl;
		bool canAfford = false;
		while (canAfford == false)
		{
			for (int i = 0; i < 5; i++)
			{
				canAfford = hotellist[i].canAfford(budget, maxRealPrice);
				hotelname = hotellist[i].getName();

				if ((canAfford == true) && (hotelname == "Four Seaons")) //to stop  looping forever
				{
					break;
				}
			}
		}

		//Choosing a Hotel

		cout << "Please choose the Hotel you would like to stay in" << endl;
		cout << "Hotel :";
		cin >> chosenHotel;
		int chosenHotelPrice;
		bool checkHotel = false;
		while (checkHotel == false)
		{
			for (int i = 0; i < 5; i++)
			{
				hotelPrice = hotellist[i].getRealPrice();
				checkHotel = hotellist[i].getHotel(chosenHotel, hotelPrice, budget);
				hotelname = hotellist[i].getName();
				if (checkHotel == true)
				{
					chosenHotelPrice = hotellist[i].getRealPrice();
					break;
				}
				else if ((checkHotel == false) && (hotelname == "FourSeasons")) //chechking  valid input 
				{
					cout << "Please enter a valid Hotel" << endl;
					cin >> chosenHotel;
				}
			}
			//ABLE TO CHOSE HOTEL YOU CANT AFFORD // Fixed
		}

		//Holiday Length

		cout << "\nHow many weeks would you like to stay at your destination for? \n This will of course effect the price of your hotel." << endl;
		cout << "Weeks : ";
		int runningPrice;
		bool validInputHotel = false;
		cin >> destLength; //ABLE TO PICK -5 WEEKS //Fixed
		while (validInputHotel == false)
		{
			if (destLength > 0)
			{
				runningPrice = calcPriceLength(destLength, chosenHotelPrice);
				holidayTotal = holidayTotal - runningPrice;
				validInputHotel = true;
			}
			else
			{
				cout << "Please enter a valid number" << endl;
				cout << "Weeks : ";
				cin >> destLength;
			}
		}

		while (holidayTotal < 0)
		{
			cout << "You dont have enough budget for this!" << endl;
			holidayTotal = budget;
			cout << "Weeks : ";
			cin >> destLength;
			runningPrice = calcPriceLength(destLength, chosenHotelPrice);
			holidayTotal = holidayTotal - runningPrice;
		}

		//Flights

		double flightsPrice = flights(destRating);
		cout << "\nYou have " << holidayTotal << " remaining" << endl;
		cout << "\nWould you like to upgrade your flights?" << endl;
		cout << "Upgrading your flights will cost " << upgradedFlights(flightsPrice) << endl;
		cout << "\n Yes or No?" << endl;
		string choiceFlights;
		cin >> choiceFlights;
		bool validInputFlights = false;
		bool holidayTotalBool = false;
		while (validInputFlights == false)
		{
			while (holidayTotalBool == false)
			{
				if (choiceFlights == "Yes")
				{
					holidayTotal = holidayTotal - upgradedFlights(flightsPrice); //adding price of upgraded flights
					if (holidayTotal >= 0)
					{
						cout << "You have " << holidayTotal << " remaining" << endl;
					}
					validInputFlights = true;
					upgradedFlightsStr = "Yes";
					holidayTotalBool = true;
				}
				else if (choiceFlights == "No")
				{
					validInputFlights = true;
					upgradedFlightsStr = "No";
					holidayTotalBool = true;
				}
				else
				{
					cout << "It looks like you may have entered an invalid response, try again" << endl;
					cout << "You have " << holidayTotal << " remaining" << endl;
					upgradedFlightsStr = "No";
					cin >> choiceFlights;
				}
			}
			if (holidayTotal <= 0)
			{
				cout << "It seems you dont have enough money to upgrade your flights" << endl;
				holidayTotal = holidayTotal + upgradedFlights(flightsPrice);
				upgradedFlightsStr = "No";
				holidayTotalBool = true;
				validInputFlights = true;
			}
		}

		//FINAL PACKAGE 

		price = budget - holidayTotal;
		
		printPackage(destName, chosenHotel, destLength, upgradedFlightsStr, price, budget);

		//Saving Holiday

		cout << "Would you like to save your holiday for later?\n Yes or No" << endl;
		string saveHolidayChoise;
		cin >> saveHolidayChoise;
		while (saveHoliday == false)
		{
			if (saveHolidayChoise == "Yes")
			{

				if (saveFile.is_open())
				{
					cout << "SAVE COMPLETE" << endl;
					saveFile << "Your Holiday Package - \n\n";
					saveFile << "Destination : " << destName << "\n";
					saveFile << "Hotel : " << chosenHotel << "\n";
					saveFile << "Holiday Length : " << destLength << "\n";
					saveFile << "Upgraded Flights? : " << upgradedFlightsStr << "\n";
					saveFile << "Price : " << price << " Budget :  " << budget << "\n";
					
					saveHoliday = true;
					saveHolidayValidInput = false;

				}
				else
				{
					cout << "Your file could not be found." << endl;
				}
				
			}
			else if (saveHolidayChoise == "No")
			{
				saveHoliday = true;
			}
			else
			{
				cout << "Please enter a valid input" << endl;
				cin >> saveHolidayChoise;
			}
		}

		//New Holiday

		cout << "Would you like to plan another holiday?\n Yes or No" << endl;
		string newHolidayChoice;
		bool validInputNewHoliday = false;
		cin >> newHolidayChoice;
		while (validInputNewHoliday == false)
		{
			if (newHolidayChoice == "Yes")
			{
				newHoliday = false;
				validInputNewHoliday = true;
			}
			else if (newHolidayChoice == "No")
			{
				newHoliday = true;
				validInputNewHoliday = true;
			}
			else
			{
				cout << "Please enter a valid choice" << endl;
				cin >> newHolidayChoice;
			}
		}

		//Would you like to save your package? // Done
		//Would you like to make plan a new holiday? // Done

	}
	saveFile.close();
	return 0;

}


void printPackage(string destName, string chosenHotel, double destLength, string upgradedFlightsStr, int total, int budget)
{
	cout << "\n------------------------------------------" << endl;
	cout << "\nYour final Holiday Package!" << endl;
	cout << "Destination : " << destName << endl;
	cout << "Hotel : " << chosenHotel << endl;
	cout << "Holiday Length: " << destLength << " weeks" << endl;
	cout << "Upgraded flights? : " << upgradedFlightsStr << endl;
	cout << "Price : " << total << " (Budget : " << budget << ")\n" << endl;
	cout << "------------------------------------------\n" << endl;
}

int calcPrice(int hotelPrice, double rating)
{
	rating = rating / 100 + 1;
	int realPrice;
	realPrice = hotelPrice * rating;
	return realPrice;
}

double calcPriceLength(double weeksMultiply, int hotelPrice)
{
	double realPrice2;
	if (weeksMultiply != 1)
	{
		weeksMultiply = weeksMultiply / 10 + 1;
		realPrice2 = hotelPrice * weeksMultiply;
		return realPrice2;
	}
	else
	{
		return hotelPrice;
	}

}

double upgradedFlights(double flights)
{
	double price;
	price = flights * 3;
	return price;
}


double flights(int destRatingNew)
{
	double multiplier = 0.0;
	double price = 0;
	int baseFlights = 200;
	double smallNumber = 0;
	smallNumber = (destRatingNew / 400.0);
	multiplier = smallNumber + 1.0;
	price = multiplier * baseFlights;
	return price;
}

void welcome()
{
	cout << "Welcome to Holiday Planner" << endl;
	cout << "\nThis program will help you plan your perfect holiday" << endl;
	cout << "\nGood luck and enjoy your trip!" << endl;
}




#include <iostream>
#include <ctime>
using namespace::std;

#include "MakeReservation.h"    // MakeReservation class definition
#include "ReservationInquiry.h" // ReservationInquiry class definition

int inputAnInteger( int begin, int end ); // input an integer in the range [ begin, end ]
Date computeCurrentDate(); // compute current date
bool leapYear( int year ); // if the year is a leap year, return true; otherwise, return false

int main()
{
   cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n";

   ReservationDatabase reservationDatabase; // reservation information database
   AvailTableDatabase availTableDatabase;   // available table information database

   MakeReservation makeReservation( reservationDatabase, availTableDatabase );
   ReservationInquiry reservationInquiry( reservationDatabase, availTableDatabase );

   bool userExited = false; // user has not chosen to exit
   int choice;

   // loop while user has not chosen option to exit system
   while( !userExited )
   {
      cout << "\n1 - Book a Table\n";
      cout << "2 - My Bookings\n";
      cout << "3 - End\n\n";

      do cout << "Enter your choice: (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );

      // decide how to proceed based on user's menu selection
      switch( choice )
      {
      case 1:
         makeReservation.execute(); // make reservation
         break;
      case 2:
         reservationInquiry.execute(); // reservation inquiry
         break;
      case 3: // user chose to exit
         userExited = true;
         cout << endl;
         break;
      default: // user did not enter an integer from 1-3
         cout << "\nIncorrect choice!" << endl;
      }
   }

   system( "pause" );
}

int inputAnInteger( int begin, int end )
{
    int temp;
    cin >> temp;
    if (begin <= temp && temp <= end)
        return temp;
    else
        return -1;
}

Date computeCurrentDate()
{
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	Date temp(1970, 1, 1);
	int seconds = time(NULL) + 8 * 60 * 60;

	int secondsPerYear = 60 * 60 * 24 * 365;
	int secondsPerMonth = 60 * 60 * 24 * 31;
	int secondsPerDay = 60 * 60 * 24;

	for (int i = 1970; i < 2000; i++) {
		if (leapYear(i))
			secondsPerYear += secondsPerDay;
		else
			secondsPerYear = 60 * 60 * 24 * 365;
		seconds -= secondsPerYear;
	}

	if (leapYear(temp.getYear()))               //Calculate year
		secondsPerYear += secondsPerDay;
	else
		secondsPerYear = 60 * 60 * 24 * 365;
	while (seconds >= secondsPerYear) {
		seconds -= secondsPerYear;
		temp.setYear(temp.getYear() + 1);
		if (leapYear(temp.getYear()))
			secondsPerYear += secondsPerDay;
		else
			secondsPerYear = 60 * 60 * 24 * 365;
	}


	if (leapYear(temp.getYear()))					//Calculate month
		days[2] = 29;
	while (seconds >= secondsPerMonth) {
		seconds -= secondsPerMonth;
		temp.setMonth(temp.getMonth() + 1);
		secondsPerMonth = 60 * 60 * 24 * days[temp.getMonth()];
	}

	while (seconds >= secondsPerDay) {				//Calculate day
		seconds -= secondsPerDay;
		temp.setDay(temp.getDay() + 1);
	}

	return temp;
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}
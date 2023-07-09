#include <iostream>
using namespace::std;

#include "ReservationInquiry.h"

extern int inputAnInteger( int begin, int end );

ReservationInquiry::ReservationInquiry( ReservationDatabase &theReservationDatabase,
                                        AvailTableDatabase &theAvailTableDatabase )
   : reservationDatabase( theReservationDatabase ),
     availTableDatabase( theAvailTableDatabase )
{
}

// reservation inquiry
void ReservationInquiry::execute()
{
   if( reservationDatabase.empty() )
   {
      cout << "\nNo reservations!\n";
      return;
   }
   cout << "\nEnter reservation number: ";
   string reservationNumber;
   cin >> reservationNumber;

   if (!reservationDatabase.exist(reservationNumber)) {
       cout << "\nNo reservations with this reservation number!\n";
       return;
   }

   cout << "\nEnter password: ";
   string password;
   cin >> password;
   cin.ignore();

   if (!reservationDatabase.legal(reservationNumber, password)) {
       cout << "\nWrong password!\n";
       return;
   }

   cout << endl;
   reservationDatabase.displayReservationInfo(reservationNumber);

   cout << "\nCancel this reservation? ( y/n ) ";
   char choise;
   cin >> choise;

   if (choise == 'y') {
       availTableDatabase.increaseAvailTables(reservationDatabase.getNumCustomers(reservationNumber), reservationDatabase.getDate(reservationNumber), reservationDatabase.getTime(reservationNumber));
       reservationDatabase.cancelReservation(reservationNumber);
       cout << "\nThis reservation has been cancelled.\n";
   }

   return;


}
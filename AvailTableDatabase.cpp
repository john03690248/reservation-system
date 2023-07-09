#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailTableDatabase.h"

// tableTypes[ i ] is the table type for i customers
const int tableTypes[ 13 ] = { 0, 1, 1, 2, 2, 3, 4, 4, 0, 0, 5, 5, 5 };

extern Date computeCurrentDate();

// calls loadAvailTables(), removes outdated available table informations and
// adds new available table informations
AvailTableDatabase::AvailTableDatabase()
{
   loadAvailTables();
                                                              //刪除舊資料
   int num[4] = { 0, 2, 2, 2 };

   Date date = computeCurrentDate();
   for (int i = 0; i < availTables.size(); i++) {
	   if (availTables[i].getDate() <= date)
		   availTables.erase(availTables.begin() + i);
   }

   if (availTables.size() == 0) {
	   date = date + 1;
	   while (availTables.size() != 30) {
		   availTables.push_back(AvailTable(date, num));
		   date = date + 1;
	   }
   }
   else {
	   while (!(availTables[availTables.size() - 1].getDate() == date + 30)) {
		   availTables.push_back(AvailTable(availTables[availTables.size() - 1].getDate() + 1, num));
	   }
   }
}

// call storeAvailTables
AvailTableDatabase::~AvailTableDatabase()
{
   storeAvailTables();
}

// increases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::increaseAvailTables( int numCustomers, Date date, int timeCode )
{
   int tableType = tableTypes[ numCustomers ];
   vector< AvailTable >::iterator it = getAvailTable( date );
   it->increaseAvailTables( timeCode, tableType );
}

// decreases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::decreaseAvailTables( int numCustomers, Date date, int timeCode )
{
   int tableType = tableTypes[ numCustomers ];
   vector< AvailTable >::iterator it = getAvailTable( date );
   it->decreaseAvailTables( timeCode, tableType );
}

// returns true if there are available tables on date for corresponding table type
bool AvailTableDatabase::availableTables( int numCustomers, Date date )
{
	for (int i = 0; i < availTables.size(); i++) {										//確認當天還有沒有座位
		if (availTables[i].getDate() == date) {
			for (int j = 1; j < 4; j++) {
				if (availTables[i].getNumAvailTables(j, tableTypes[numCustomers]))
					return true;
			}
			return false;
		}
	}
}

// returns true if there are available tables on date and timeCode for corresponding table type
bool AvailTableDatabase::availableTables( int numCustomers, Date date, int timeCode )
{
	for (int i = 0; i < availTables.size(); i++) {										//確認當時還有沒有座位
		if (availTables[i].getDate() == date) {
			if (availTables[i].getNumAvailTables(timeCode, tableTypes[numCustomers]))
				return true;
			else
				return false;
		}
	}
}

void AvailTableDatabase::loadAvailTables()
{
	ifstream inFile("AvailTables.dat", ios::in | ios::binary);				//讀檔
	if (!inFile) {
		cout << "File could not be opened.\n";
		system("pause");
		exit(1);
	}
	inFile.seekg(0, ios::end);
	int count = inFile.tellg() / sizeof(AvailTable);
	inFile.seekg(0, ios::beg);
	AvailTable temp;
	for (int i = 0; i < count; i++) {
		inFile.read(reinterpret_cast <char*> (&temp), sizeof(AvailTable));
		availTables.push_back(temp);
	}
	inFile.close();
}

void AvailTableDatabase::storeAvailTables()
{
	ofstream outFile("AvailTables.dat", ios::out | ios::binary);			//寫檔
	if (!outFile) {
		cout << "File could not be opened.\n";
		system("pause");
		exit(1);
	}
	for (int i = 0; i < availTables.size(); i++) {
		outFile.write(reinterpret_cast <char*> (&availTables[i]), sizeof(AvailTable));
	}
	outFile.close();
}

// returns an iterator that points to the AvailTable object containing specified date
vector< AvailTable >::iterator AvailTableDatabase::getAvailTable( Date date )
{
	vector <AvailTable>::iterator temp = availTables.begin();
	for (; temp != availTables.end(); temp++) {
		if (temp->getDate() == date)
			return temp;
	}
}
#include<iostream>
#include"mysql.h"
#include<mysqld_error.h>
#include<windows.h>
#include<sstream>

using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "";  // password
const char* DB = "HostelReservationSystemDB";

class Hostel {
private:
	string Name;
	int Bed, Fee;

public:

	Hostel(string name, int bed, int fee)
	{
		Name = name;
		Bed = bed;
		Fee = fee;

	}
	string getName()
	{
		return Name;
	}

	int getBed()
	{
		return Bed;
	}

	int getFee()
	{
		return Fee;
	}



};

int main()
{

	MYSQL* conn;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0))
	{
		cout << "Error: " << mysql_error(conn)<<endl;
	}
	else
	{
		cout << "Logged in Database" << endl;
	}

	Sleep(3000);

	Hostel h("3star", 5, 5000);

	int intB = h.getBed();
	stringstream ss;    //using ssstream library

	ss << intB;

	string strB = ss.str();  // converting bed to string

	int intF = h.getFee();
	stringstream as;
	as << intF;
	string strF = as.str();

	string insert ="INSERT INTO hostel (Name, Bed, Fee) VALUES ('"+h.getName()+"','"+strB+"', '"+strF+"' )";
	if (mysql_query(conn, insert.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
	}

	else
	{
		cout << "Data inserted" << endl;
	}

	bool exit = false;
	while (!exit)
	{
		system("cls");

		cout << "Welcome To Hostel Reservation System" << endl;
		cout << "****************************************" << endl;
		cout<<"1. Reserve Bed"<<endl;
		cout << "2. Exit: " << endl;
		cout << "Enter Your Choice: ";
		int val;
		cin >> val;

		if (val == 1)
		{
			string nameOfStudent;
			cout << "Enter Student Name: ";
			cin >> nameOfStudent;
			int totalBedAvailable;

			string checkIfBedAvailable = "SELECT Bed FROM hostel Name = '" + h.getName() + "'";
			if (mysql_query(conn, checkIfBedAvailable.c_str()))
			{
				cout << "Error: " << mysql_error(conn) << endl;
			}

			else
			{
				MYSQL_RES* res;
				res = mysql_store_result(conn); // api call

				if (res)
				{
					MYSQL_ROW row = mysql_fetch_row(res); // api call

					if (row)
					{
						totalBedAvailable = atoi(row[0]);
					}


					mysql_free_result(res);
				}
			}

			if (totalBedAvailable > 0)
			{
				totalBedAvailable--;
				stringstream zs;
				zs << totalBedAvailable;
				string strT = zs.str();

				string updateTotalInDb = "UPDATE hostel SET Bed = '" + strT + "', WHERE Name= '" + h.getName() + "'";  // updating value of total bed in database

			
				if (mysql_query(conn, updateTotalInDb.c_str()))
				{
					cout << "Error: " << mysql_error(conn) << endl;
				}
				else
				{

					cout << "Bed is Reserved Successfully in " << h.getName() << " Hostel For Student " << nameOfStudent << endl;
					cout << "Please Pay " << h.getFee() << " Rupees." << endl;

				}
			}

			else if (totalBedAvailable == 0)
			{
				cout << "Sorry! No Bed Available " << endl;
			}

			Sleep(8000);


		}// if option 1 selected

		else if (val == 2)
		{
			exit = true;
			cout << "Good Luck " << endl;
			Sleep(3000);

		}// if option 2 selected i.e the client want to exit

		else
		{
			cout << "Invalid Input" << endl;
			Sleep(3000);
		}

	}// while

	mysql_close(conn);

	std::cout << "hello" << std::endl;
  
}

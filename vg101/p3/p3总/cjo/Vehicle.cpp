#include "Vehicle.h"
using namespace std;

Vehicle::Vehicle(string lp, string tp, int fl, int col) {
	this->licensePlate = move(lp);
	this->type = move(tp);
	this->floor = fl;
	this->column = col;
}
void Vehicle::arrive(vector<vector<string>>& parkingArea) {
	time(&arrTime); //time() is a function in the library <time.h>
	parkingArea[this->floor][this->column] = "X"; 
	}
	/*when the car has parked into the parkingarea, then replaced the type of this
	parkingarea by "X",
	which represents that this parking area has been occupied. 
	*/
void Vehicle::depart(vector<vector<string>>& parkingArea) {
	time(&depTime);
	parkingArea[this->floor][this->column] = this->type; //change "X" into the type, which represents that the slot is free again.
}
double Vehicle::timeSpent() {
	return difftime(depTime, arrTime); //calculate time2-time1 and returns the result with double type
}
double Vehicle::getPrice(double price) {
	return timeSpent() * price;
}
string Vehicle::getArrTime() {
	//char temp[32];
	string time;
	//tm* timeinfo = (tm*)malloc(sizeof(tm));
	//localtime_s(timeinfo, &arrTime);
	//asctime_s(temp, timeinfo);
	time = asctime(localtime(&arrTime));

	//time = temp;
	//free(timeinfo);
//	time = asctime(localtime(&arrTime));
	return time;
} //switch the type of time from time_t to string for output(print).
bool  Vehicle::querySlot(vector<vector<string>> parkingArea) { //pass the parkingarea to the "searching car" function
	for (int i = 0; i < parkingArea.size(); ++i) { // parkingArea.size means the number of parkingarea rows
		for (int j = 0; j < parkingArea[i].size(); ++j) { //parkingArea[i].size means the number of parkingarea colums
			if (parkingArea[i][j] == type) 
			{
				this->floor = i;
				this->column = j; //park the car
				return true; //means find the parking slot
			}
		}
	}
	return false; //means not found
}
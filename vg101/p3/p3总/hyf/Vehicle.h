#pragma once
#include<string>
#include<time.h>
#include<vector>

using namespace std;
class Vehicle
{
public:
	string licensePlate;
	string type;
	int floor;
	int column;
	time_t arrTime;
	time_t depTime;

	Vehicle() {};
	Vehicle(string lp, string tp,int fl, int col);
	void arrive(vector<vector<string>>& parkingArea);
	void depart(vector<vector<string>>& parkingArea);
	double timeSpent();
	double getPrice(double price);
	string getArrTime();
	bool querySlot(vector<vector<string>> parkingArea);
};


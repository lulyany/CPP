#pragma once
#include<string>
#include<iostream>
#include<time.h>
using namespace std;
class Ticket
{
private:
	
public:
	string type;
	virtual void printTicket() = 0; 
};
//virtual function

class ArrTicket:public Ticket
//derived from Ticket 
{
private:
	string time;
	int floor;
	int column;
public:
	ArrTicket(string time, int floor, int column, string type);
	void printTicket() override;
};

class DepTicket :public Ticket { 
private:
	int timeSpent;
	double price;
public:
	DepTicket(int timeSpent, double price, string type);
	void printTicket() override;
};
//derived from Ticket


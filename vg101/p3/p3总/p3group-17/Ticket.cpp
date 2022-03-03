#include "Ticket.h"
ArrTicket::ArrTicket(string time, int floor, int column, string type) {
	this->time = move(time); //when we write time, the computer will recognize it as 'this->time'
	this->floor = floor;
	this->column = column;
	this->type = move(type);
}
void ArrTicket::printTicket() {
	cout << "****************************************" << endl;
	cout << "Time of arrival: " << this->time;
	cout << "Type of vehicle: " << this->type << endl;
	cout << "Please go to parking space " << this->column+1 << " on the " << this->floor+1 << " floor!" << endl;
	cout << "****************************************" << endl;
}

DepTicket::DepTicket(int timeSpent, double price, string type) {
	this->price = price;
	this->timeSpent = timeSpent;
	this->type = move(type);
	
}
void DepTicket::printTicket() {
	cout << "****************************************" << endl;
	cout << "Time spent in the paring lot: " << this->timeSpent << "s" << endl;
	cout << "Type of vehicle: " << this->type << endl;
	cout << "Price: " << this->price  << endl;
	cout << "****************************************" << endl;
}
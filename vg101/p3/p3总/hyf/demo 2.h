#pragma once
#include<vector>
#include<map>
#include<string>
#include <iostream>

#include"Vehicle.h"
#include"Ticket.h"
using namespace std;
map<string, double> chargeStan;
vector<Vehicle*> vehinLot;
vector<vector<string>> parkingArea = { {"Car","Car","Motorbike","Motorbike","Bicycle","Bicycle","Van","Van"} ,   //row: floor | column: number
										{"Car","Car","Motorbike","Motorbike","Bicycle","Bicycle","Van","Van"} ,
										{"Car","Car","Motorbike","Motorbike","Bicycle","Bicycle","Van","Van"} ,
										{"Car","Car","Motorbike","Motorbike","Bicycle","Bicycle","Van","Van"} };
									//vector used as two demensinal array.
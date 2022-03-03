#include"demo.h"
#include<iostream>
using namespace std;
//#define CAR 1
//#define MOTORBIKE 2
//#define BYCYCLE 3
//#define VAN 4

//bool querySlot(vector<vector<string>> parkingArea, string type,int& floor,int& coulumn) {
//	for (int i = 0; i < parkingArea.size(); ++i) {
//		for (int j = 0; j < parkingArea[i].size(); ++j) {
//			if (parkingArea[i][j] == type)
//			{
//				floor = i;
//				coulumn = j;
//				return true;
//			}
//		}
//	}
//	return false;
//}

int main()
{
	
	//vector<vector<int>> parkingArea = { {CAR,CAR,MOTORBIKE,MOTORBIKE,BYCYCLE,BYCYCLE,VAN,VAN} ,
	//									{CAR,CAR,MOTORBIKE,MOTORBIKE,BYCYCLE,BYCYCLE,VAN,VAN} ,
	//									{CAR,CAR,MOTORBIKE,MOTORBIKE,BYCYCLE,BYCYCLE,VAN,VAN} ,
	//									{CAR,CAR,MOTORBIKE,MOTORBIKE,BYCYCLE,BYCYCLE,VAN,VAN} };
	vector<vector<string>> parkingArea = { {"Car","Car","Motorbike","Motorbike","Bicycle","Bicycle","Van","Van"} ,   //row: floor | column: number
										{"Car","Car","Motorbike","Motorbike","Bicycle","Bicycle","Van","Van"} ,
										{"Car","Car","Motorbike","Motorbike","Bicycle","Bicycle","Van","Van"} ,
										{"Car","Car","Motorbike","Motorbike","Bicycle","Bicycle","Van","Van"} };
	map<string, double> chargeStan;
	vector<Vehicle*> vehinLot;
	cout << "****************************Welcom****************************" << endl;
	cout << "Please complete some initialization operations first! " << endl;
	cout << "Set price for each Vehicle(Yuan per second)" << endl;
	chargeStan.insert(make_pair("Car", 0)); // insert <"Car",0>to map, "Car" is the type ,"0" is the unit price
	chargeStan.insert(make_pair("Motorbike", 0));
	chargeStan.insert(make_pair("Bycycle", 0));
	chargeStan.insert(make_pair("Van", 0));
	for (auto &iter : chargeStan) { //decide the type automatically
		cout << iter.first << ": ";
		cin >> iter.second;
	}
	cout << "Initial Complete!" << endl;
	cout << "-------------------------------------------" << endl; //parkingarea and the price has been initialized
	while (1) {
		cout << "Are there vehicles entering or leaving the parking lot(1.entering/0.departing):";
		int inOrout;
		cin >> inOrout;
		cout << endl;
		if (inOrout == 1) {
			string inLp; //license plate
			int cinType; //car type 
			string type;
			bool isPark;
			int floor = 0;
			int coulumn = 0;
			cout << "Please Enter Vehicle Information!" << endl;
			cout << "Please input license plate: ";//used to find the car
			cin >> inLp; //the license plate of car that comes in
			cout << "Please select vehicle type(1.Car|2.Motorbike|3.Bycycle|4.Van): ";
			cin >> cinType; //input the car type
			switch (cinType) 
			{
			case 1:
				type = "Car";
				break;
			case 2:
				type = "Motorbike";
				break;
			case 3:
				type = "Bicycle";
				break;
			case 4:
				type = "Van";
				break;
			default:
				cout << "Wrong Type!You can't Part Here!" << endl;
				continue;
			}

			cout << "Checking parking space remaining" << endl;

			Vehicle* veh = new Vehicle(inLp, type, floor, coulumn);
			isPark = veh->querySlot(parkingArea); //this function returns 0 or 1;
			if (isPark) {
				veh->arrive(parkingArea);
				cout << "Arrival ticket print......." << endl;
				cout << endl;
				ArrTicket* arrT = new ArrTicket(veh->getArrTime(), veh->floor, veh->column, veh->type);
				arrT->printTicket();
				cout << endl;
				cout << "Arrival ticket print complete!" << endl;
				cout << "-------------------------------------------" << endl;
				vehinLot.push_back(veh); //a container which contains veh (our vehicles)
				delete arrT;
			}
			else {
				delete veh;
				cout << "Sorry, the parking space is full!" << endl;
				cout << "-------------------------------------------" << endl;
			}
		}
		else if (!inOrout) { //cars go out
			string outLp;
			if (vehinLot.empty()) //if vector equals to 0, that means no car will go out
			{
				cout << "The Parking Lot is Empty!" << endl;
				cout << "-------------------------------------------" << endl;
			}
			else {
				cout << "Please Enter LisensePlate Going to Depart: ";
				cin >> outLp;
				bool isFind = false;
				int vehIndex;
				for (int i = 0; i < vehinLot.size(); ++i) {
					if (vehinLot[i]->licensePlate == outLp) //decide whether the license plate of the car in the vector= the license plate of the car that goes out
					{
						vehIndex = i; //get the number of the car that goes out
						isFind = true; 
					}
				}
				if (isFind) {
					double vehPrice;
					vehinLot[vehIndex]->depart(parkingArea);
					cout << "Departure Ticket print....." << endl;
					cout << endl;
					for (auto &iter : chargeStan) {
						if (iter.first == vehinLot[vehIndex]->type)
							vehPrice = iter.second;
					}
					DepTicket* depT = new DepTicket(vehinLot[vehIndex]->timeSpent(), vehinLot[vehIndex]->getPrice(vehPrice), vehinLot[vehIndex]->type);
					depT->printTicket();
					cout << endl;
					cout << "Departure ticket print complete!" << endl;
					cout << "-------------------------------------------" << endl;
					delete depT;
					delete vehinLot[vehIndex];
					vehinLot.erase(vehinLot.begin() + vehIndex);
				}
				else {
					cout << "Sorry,Vehicle Not Found!" << endl;
					cout << "-------------------------------------------" << endl;
				}
			}
		}
		else
		{
			cout << "Wrong Command, Please Enter Again!" << endl;
			cout << "-------------------------------------------" << endl;
			continue;
		}		
	}
}
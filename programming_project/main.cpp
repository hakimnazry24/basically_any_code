#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#define ROW_SIZE 20

using namespace std;

struct BusDetail
{
	int busNo;
	string name;
	float rate;
	string destination;
};

void DisplayBusRecord();
void GetRentalInformation(int*, int*);
int CalculateRentalCost(int, int);
void GetComplain();
void GetRepairCost();
void AddBusRecord();
void CustomerScreen();
void AdminScreen();

float totalRentalCost = 0;
float totalRepairCost = 0;

ifstream inNameRecord;
ifstream inRateRecord;
ifstream inDestinationRecord;
ifstream inBusNoRecord;
ofstream outNameRecord;
ofstream outRateRecord;
ofstream outDestinationRecord;
ofstream outBusNoRecord;

int main(){
    int option;
    cout << "Welcome to TBS Bus Rental Terminal" << endl;
	
	//choose to enter customer screen, admin screen or exit terminal
    do{
		cout << "\nPress '1' to make access customer screen\nPress '2' to access administrator screen\nPress '0' to exit terminal\nOption: ";
		cin >> option;
    	if(option == 1){
    		CustomerScreen();
		}
		else if(option == 2){
			AdminScreen();
		}
		else if(option == 0){
			break;
		}
		else{
			cout << "Invalid input!!. Please enter correct input." << endl;
		}
	}while(option != 0);
	
	cout << "Thank you for using our terminal system." << endl;
	cout << "Total rental cost: RM " << totalRentalCost << endl;
	cout << "Total repair cost: RM " << totalRepairCost << endl;
	
	//press any key to terminate program
	system("pause");

    return 0;
}
void CustomerScreen(){
	int busNo;
	int rentalDay;
	int rentalCost;
	int option;
	cout << "You are in customer screen." << endl;
	
	//choose to make bus rental, make complain, or exit customer screen
	do{
		cout << "Press '1' to make bus rental\nPress '2' to make complain regarding our services\nPress '0' to exit from customer screen" << endl;
		cin >> option;
		if(option == 1){
			DisplayBusRecord();
			GetRentalInformation(&busNo, &rentalDay);
			rentalCost = CalculateRentalCost(busNo, rentalDay);
			totalRentalCost += rentalCost;
		}
		else if(option == 2){
			GetComplain();
		}
		else if(option == 0){
			return;
		}
		else{
			cout << "Invalid input!!. Please enter correct input." << endl;
		}
	}while(option != 0);
}
void AdminScreen(){
	AddBusRecord();
//	DeleteBusRecord();
}

void DisplayBusRecord(){
	string readData;
	
	string nameRecord = "bus_name_record.dat";
	string rateRecord = "bus_rate_record.dat";
	string destinationRecord = "bus_destination_record.dat";
	string busNoRecord = "bus_busno_record.dat";
	
	//open files in read mode
	inBusNoRecord.open(busNoRecord.c_str(), ios::in);
	inNameRecord.open(nameRecord.c_str(), ios::in);
	inRateRecord.open(rateRecord.c_str(), ios::in);
	inDestinationRecord.open(destinationRecord.c_str(), ios::in);
	
	cout<<"Bus rental rates for a day in KL:"<<endl;
	cout<<endl;
	
	cout<<"BusNo     "<<" | "<<"   Bus Company"<<"   "<<"|         Rate     "<<" | "<<"Destination";
	cout<<endl;
	
	//display all records
	while(!inBusNoRecord.eof() && !inNameRecord.eof() && !inRateRecord.eof() && !inDestinationRecord.eof()){
		getline(inBusNoRecord, readData);
		cout << readData << "\t\t";
		getline(inNameRecord, readData),
		cout << readData << "\t\t";
		getline(inRateRecord, readData),
		cout << readData << "\t\t";
		getline(inDestinationRecord, readData),
		cout << readData << "\t\t";
		cout << endl;
	}
	inBusNoRecord.close();
	inNameRecord.close();
	inRateRecord.close();
	inDestinationRecord.close();
	
}
void GetRentalInformation(int* busNoPtr, int* rentalDayPtr){
	int busNo, rentalDay;
	
	//get busNo and rentalDay and pass by pointer
	cout << "Enter bus no: ";
	cin >> *busNoPtr;
	cout << "Enter total of rental day: ";
	cin >> *rentalDayPtr;
}

int CalculateRentalCost(int busNo, int rentalDay){ 
	string rateRecord = "bus_rate_record.dat";
	string line;
	int rateArr[ROW_SIZE];
	int i = 0;
	int cost;
	
	inRateRecord.open(rateRecord.c_str(), ios::in);
	
	//store rate into array
	while(!inRateRecord.eof()){
		inRateRecord >> rateArr[i];
		getline(inRateRecord, line);
		i++;
	}
	//calculate cost
	cost = rateArr[busNo] * rentalDay;
	
	inRateRecord.close();

	return cost;
	
}
void GetComplain(){
	
	
}
void GetRepairCost(){
	
}
void AddBusRecord(){
	string nameRecord = "bus_name_record.dat";
	string rateRecord = "bus_rate_record.dat";
	string destinationRecord = "bus_destination_record.dat";
	string busNoRecord = "bus_busno_record.dat";
	BusDetail bus;
	
	//get input 
	cout << "Enter basNo: ";
	cin >> bus.busNo;
	
	cout << "Enter bus name: ";
	cin >> bus.name;
	
	cout << "Enter rate: ";
	cin >> bus.rate;
	
	cout << "Enter destination of the bus: ";
	cin >> bus.destination;
	
	//open .dat file in append mode
	outBusNoRecord.open(busNoRecord.c_str(),ios::out | ios::app);
	outNameRecord.open(nameRecord.c_str(),ios::out | ios::app);
	outRateRecord.open(rateRecord.c_str(), ios::out | ios::app);
	outDestinationRecord.open(destinationRecord.c_str(), ios::out | ios::app);
	
	//terminate program if file access fail
	if(outNameRecord.fail()){				
		cout << "The bus_name_record.dat file was not successfully opened" << endl; 
		exit(1);
	}
	if(outRateRecord.fail()){				
		cout << "The bus_rate_record.dat file was not successfully opened" << endl; 
		exit(1);
	}
	if(outDestinationRecord.fail()){				
		cout << "The bus_destination_record.dat file was not successfully opened" << endl; 
		exit(1);
	}
	if(outBusNoRecord.fail()){
		cout << "The bus_busno_record.dat file was not successfully opened" << endl; 
		exit(1);
	}
			
	//append data to file
	outBusNoRecord<< bus.busNo << endl;
	outNameRecord << bus.name << endl;
	outRateRecord << bus.rate << endl;
	outDestinationRecord << bus.destination << endl;
	
	//close file
	outBusNoRecord.close();
	outNameRecord.close();
	outRateRecord.close();
	outDestinationRecord.close();
	cout << "Record has been added" << endl;
}

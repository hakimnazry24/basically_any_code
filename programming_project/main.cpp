#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#define RATEARR_ROW 2
#define RATEARR_COL 20

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
void GetComplainAndRepairCost();
void GetRepairCost();
void AddBusRecord();
void CustomerScreen();
void AdminScreen();
void DisplayTotal();

float totalRentalCost = 0;
float totalRepairCost = 0;

ifstream inNameRecord;
ifstream inRateRecord;
ifstream inDestinationRecord;
ifstream inBusNoRecord;
ifstream inComplainRecord;
ofstream outNameRecord;
ofstream outRateRecord;
ofstream outDestinationRecord;
ofstream outBusNoRecord;
ofstream outComplainRecord;

int main(){
    int option;
    
	//choose to enter customer screen, admin screen or exit terminal
    do{
    	system("cls");
    	cout << "\n\n\n\n\n\n";
		cout << "\t\t\t1. Enter customer screen\n\t\t\t2. Enter administrator screen\n\t\t\t0. Exit terminal\n\t\t\tOption:  ";
		cin >> option;
    	if(option == 1){
    		system("cls");
    		CustomerScreen();
		}
		else if(option == 2){
			system("cls");
			AdminScreen();
		}
		else if(option == 0){
			break;
		}
		else{
			system("cls");
			cout << "Invalid input!!. Please enter correct input." << endl;
		}
	}while(true);
	
	system("cls");
	cout << "\n\n\n\n\n\n\t\t\tThank you for using the terminal." << endl;
	
	//press any key to terminate program
	cout << "\t\t\t";
	system("pause");

    return 0;
}
void CustomerScreen(){
	system("cls");
	int busNo = 0;
	int rentalDay = 0;
	int rentalCost = 0;
	int option;
	
	//choose to make bus rental, make complain, or exit customer screen
	do{
		cout <<"\n\n\n\n\n\n";
		cout << "\t\t\tYou are in customer screen." << endl;
		cout << "\t\t\t1. Make bus rental\n\t\t\t2. Lodge complain\n\t\t\t0. Exit customer screeen\n\t\t\tOption: " ;
		cin >> option;
		if(option == 1){
			system("cls");
			DisplayBusRecord();
			GetRentalInformation(&busNo, &rentalDay);
				
			rentalCost = CalculateRentalCost(busNo, rentalDay);
			totalRentalCost += rentalCost;
		}
		else if(option == 2){
			system("cls");
			GetComplainAndRepairCost();
		}
	else if(option == 0){
		system("cls");
		return;
		}
		else{
			system("cls");
			cout << "Invalid input!!. Please enter correct input." << endl;
		}
		system("cls");
	}while(option != 0);
}
void AdminScreen(){
	system("cls");
	int option;
	
	//choose to add bus record, review and get repair cost or exit terminal
	do{
		system("cls");
		cout << "\n\n\n\n\n\n";
		cout << "\t\t\tYou are in administrator screen." << endl;
		cout << "\t\t\t1. Add new bus information\n\t\t\t2. Display total collection and repair cost in a month\n\t\t\t0. Exit administrator terminal\n\t\t\tOption: ";
	
		cin >> option;
		if(option == 1)
			AddBusRecord();
		else if(option == 2)
			DisplayTotal();
//		else if(option == 0)
//			return;
		else
			cout << "Invalid input!!. Please enter correct input." << endl;
	}while(option != 0);
}

void DisplayBusRecord(){
	string readData;
	
	string busNoRecord = "bus_busno_record.dat";
	string nameRecord = "bus_name_record.dat";
	string rateRecord = "bus_rate_record.dat";
	string destinationRecord = "bus_destination_record.dat";
	
	//open files in read mode
	inBusNoRecord.open(busNoRecord.c_str(), ios::in);
	inNameRecord.open(nameRecord.c_str(), ios::in);
	inRateRecord.open(rateRecord.c_str(), ios::in);
	inDestinationRecord.open(destinationRecord.c_str(), ios::in);
	
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
	
	cout<<"\n\n\n\n\n\n\t\t\tBus rental rates for a day in KL:"<<endl;
	cout<<endl;
	
	cout <<"|BusNo     "<<"|"<<"     Bus Company     "<<"|"<<"     Rate (/day)     "<<"|"<<"     Destination|" << endl;
	
	//display all records
	while(!inBusNoRecord.eof() && !inNameRecord.eof() && !inRateRecord.eof() && !inDestinationRecord.eof()){
		getline(inBusNoRecord, readData);
		cout << " " <<readData << "\t\t";
		getline(inNameRecord, readData);
		cout << readData << "\t\t";
		getline(inRateRecord, readData);
		cout << readData << "\t\t";
		getline(inDestinationRecord, readData);
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
	cout << "\t\t\tEnter bus no: ";
	cin >> *busNoPtr;
	cout << "\t\t\tEnter total of rental day: ";
	cin >> *rentalDayPtr;
	
	cout << "\n\t\t\tThank you for using our service." << endl;
	cout << "\n\t\t\t";
	system("pause");
}

int CalculateRentalCost(int busNo, int rentalDay){ 
	string busNoRecord = "bus_busno_record.dat";
	string rateRecord = "bus_rate_record.dat";
	
	string line;
	int rate = 0;
	int rateArr[RATEARR_ROW][RATEARR_COL];
	int i = 0;
	int cost;
	
	inRateRecord.open(rateRecord.c_str(), ios::in);
	inBusNoRecord.open(busNoRecord.c_str(), ios::in);
	
	if(inRateRecord.fail()){
		cout << "\t\t\tThe bus_rate_record.dat was not succesfully opened" << endl;
		exit(1);
	}
	if(inBusNoRecord.fail()){
		cout << "\t\t\tThe bus_busno_recor.dat was not successfully opened" << endl;
		exit(1);
	}
	
	//store bus_busNo_record.dat data into rateArr
	while(!inBusNoRecord.eof()){
		inBusNoRecord >> rateArr[0][i];
		getline(inBusNoRecord, line);
		//cout << rateArr[0][i] << endl;
		i++;
	}
	
	i = 0;
	//store bus_rate_record.dat data into rateArr
	while(!inRateRecord.eof()){
		inRateRecord >> rateArr[1][i];
		getline(inRateRecord, line);
		//cout << rateArr[1][i] << endl;
		i++;
	}
	
	//get rate of bus from rateArr according to busNo
	i = 0;
	while(true){
		if(busNo == rateArr[0][i]){
			rate = rateArr[1][i];
			//cout << rate << endl;
			break;
		}
		i++;
	}
	
	inBusNoRecord.close();
	inRateRecord.close();
	
	//calculate cost of bus rental
	return rentalDay * rate;
	
	//inBusNoRecord.close();
	//inRateRecord.close();
}
void GetComplainAndRepairCost(){
	system("cls");
	int complainNo;
	string otherComplain;
	
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\tComplain no |\t\t Description" << endl;
	cout << "\t\t\t1\t\t Air conditioner not working" << endl;
	cout << "\t\t\t2\t\t Window damage" << endl;
	cout << "\t\t\t3\t\t Seat damage" << endl;
	cout << "\t\t\t4\t\t Interior light damage damage" << endl;
	cout << "\t\t\t5\t\t Television damage" << endl;
	cout << "\t\t\t6\t\t Radio damage" << endl;
	cout << "\t\t\t0\t\t Other" << endl;
	cout << "\t\t\tEnter complain no: ";
	
	do{
		cin >> complainNo;
		switch(complainNo){
			case 1: totalRepairCost += 700; break;
			case 2: totalRepairCost += 400; break;
			case 3: totalRepairCost += 500; break;
			case 4: totalRepairCost += 200; break;
			case 5: totalRepairCost += 300; break;
			case 6: totalRepairCost += 100; break;
			case 0: cout << "\t\t\tEnter your complain: ";
					cin >> ws;
					getline(cin, otherComplain);
					break;
					
			default: cout << "\t\t\tInvalid input! Enter a valid complain no" << endl;
		}
		
	}while(complainNo != 1 && complainNo != 2 && complainNo != 3 && complainNo != 4 && complainNo != 5 && complainNo != 6 && complainNo != 0);
	
	cout << "\t\t\tThank you for your feedback." << endl;
	cout << "\n\t\t\t";
	system("pause");
}

void AddBusRecord(){
	system("cls");
	string busNoRecord = "bus_busno_record.dat";
	string nameRecord = "bus_name_record.dat";
	string rateRecord = "bus_rate_record.dat";
	string destinationRecord = "bus_destination_record.dat";

	BusDetail bus;
	
	cout << "\n\n\n\n\n\n";
	//get input 
	cout << "\t\t\tEnter basNo: ";
	cin >> bus.busNo;
	
	cout << "\t\t\tEnter bus name: ";
	cin >> bus.name;
	
	cout << "\t\t\tEnter rate: ";
	cin >> bus.rate;
	
	cout << "\t\t\tEnter destination of the bus: ";
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
	cout << "\t\t\tRecord has been added" << endl;
	cout << "\n\t\t\t";
	system("pause");
	
}

void DisplayTotal(){
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\tTotal bus rental collection this month: RM " << totalRentalCost << endl;
	cout << "\t\t\t Estimated total repair cost this month: RM " << totalRepairCost << endl;
	cout << "\n\t\t\t";
	system("pause");
} 

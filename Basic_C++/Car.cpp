#include <iomanip>
#include <iostream>
#include "Car.h"
#include "Mylibrary.h"
#include <fstream>

using namespace std;

unsigned int Car::input_mscn_[MSCN_ARRAY_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0 };//save input id
bool Car::power_on = true;//true when the car is on and false when the car is off
char Car::gear_ = 'N';
Car::Screen Car::screen_ = Screen::kNPScreen;//save id screen
unsigned int Car::speed_ = 0;

Car::Car() {
	for (size_t i = 0; i < MSCN_ARRAY_SIZE; i++) mscn_[i] = 0;
	for (size_t i = 0; i < 3; i++)warning_speed_[i] = 0;
}

void Car::Run(string datafile) {
	if (Loginandsetup(datafile))
		Menu();
	else
	{
		system("cls");
		cout << "DANG NHAP THAT BAI! DA TAT MAY!\nHen gap lai ban sau\n" << endl;
	}
}

// the function works login and setup 
// parameter is datafile
// return true if logged in succesfully, return false if login failed
bool Car::Loginandsetup(string datafile) {
	if (ReadData(datafile))
	{
		//the car has data
		system("cls");
		InputMSCN();
		if (CheckMSCN())
		{
			//logged in succesfully
			system("cls");
			cout << "DANG NHAP THANH CONG !" << endl;

			cout << "MANG NHAP VAO TRUOC KHI SAP XEP: ";
			Printarray(input_mscn_, MSCN_ARRAY_SIZE);
			unsigned int input_mscn_clone[MSCN_ARRAY_SIZE];
			copy_n(input_mscn_, MSCN_ARRAY_SIZE, input_mscn_clone);
			Bubblesort(input_mscn_clone, MSCN_ARRAY_SIZE);
			cout << "--> MANG NHAP VAO SAU KHI SAP XEP: ";
			Printarray(input_mscn_clone, MSCN_ARRAY_SIZE);

			cout << "MA SO CA NHAN TRUOC KHI SAP XEP: ";
			Printarray(mscn_, MSCN_ARRAY_SIZE);
			unsigned int mscn_clone[MSCN_ARRAY_SIZE];
			copy_n(mscn_, MSCN_ARRAY_SIZE, mscn_clone);
			Selectionsort(mscn_clone, MSCN_ARRAY_SIZE);
			cout << "--> MA SO CA NHAN SAU KHI SAP XEP: ";
			Printarray(mscn_clone, MSCN_ARRAY_SIZE);

			cout << endl;
			system("pause");

			ReinstallMSCN();
			Reinstallwarningspeed();

			//update data
			WriteData(datafile);
			return true;
		}
	}
	else
	{
		//the first registration or can not read data
		system("cls");
		cout << "MA SO CA NHAN CHUA DUOC CAI DAT!" << endl;
		InputMSCN();
		copy_n(input_mscn_, MSCN_ARRAY_SIZE, mscn_);
		ReinstallMSCN();
		system("cls");

		cout << "TOC DO CANH BAO KHOANG CACH AN TOAN CHUA DUOC CAI DAT!" << endl;
		Installwarningspeed();
		Reinstallwarningspeed();
		WriteData(datafile);
		return true;
	}
	return false;
}

//require user enter id and save it in input_mscn
void Car::InputMSCN() {
	cout << "NHAP MA SO CA NHAN, MANG " << setfill('0') << setw(2) << MSCN_ARRAY_SIZE << " so: " << endl;
	for (size_t i = 0; i < MSCN_ARRAY_SIZE; i++)
	{
		cout << "SO THU " << i + 1 << " : ";
		string str = "";
		getline(cin, str);
		while (!Isunsignedinterger(str)) {
			cout << "--> NHAP KHONG HOP LE, VUI LONG NHAP LAI: " << endl;
			getline(cin, str);
		}
		input_mscn_[i] = stoi(str);
	}
}

// check id, compare input_mscn with mscn_
bool Car::CheckMSCN() {
	unsigned int mscn_clone[MSCN_ARRAY_SIZE];
	unsigned int input_mscn_clone[MSCN_ARRAY_SIZE];
	copy_n(mscn_, MSCN_ARRAY_SIZE, mscn_clone);
	copy_n(input_mscn_, MSCN_ARRAY_SIZE, input_mscn_clone);
	Selectionsort(mscn_clone, MSCN_ARRAY_SIZE);
	Bubblesort(input_mscn_clone, MSCN_ARRAY_SIZE);
	for (size_t i = 0; i < MSCN_ARRAY_SIZE; i++)
	{
		if (mscn_clone[i] != input_mscn_clone[i])
			return false;
	}
	return true;
}

//announce that the id has been installed
//asking if user wants to reinstall? 
void Car::ReinstallMSCN() {
	system("cls");
	cout << "MA SO CA NHAN DA DUOC CAI DAT: ";
	Printarray(mscn_, MSCN_ARRAY_SIZE);
	cout << endl;
	cout << "BAN CO MUON CAI DAT LAI MA SO CA NHAN KHONG? ";
	if (YNQuestion())
	{
		system("cls");
		InputMSCN();
		copy_n(input_mscn_, MSCN_ARRAY_SIZE, mscn_);
		ReinstallMSCN();
	}
}

//installing warning speed range and save it in warning_speed array
void Car::Installwarningspeed() {
	cout << "CAI DAT VAN TOC CANH BAO KHOANG CACH AN TOAN VOI 3 MUC VAN TOC: " << endl;
	for (size_t i = 0; i < 3; i++)
	{
		cout << "VAN TOC MUC " << i + 1 << " : ";
		string str = "";
		getline(cin, str);
		while (!Isunsignedinterger(str)) {
			cout << "--> NHAP KHONG HOP LE, VUI LONG NHAP LAI: " << endl;
			getline(cin, str);
		}
		warning_speed_[i] = stoi(str);
	}
}

//announce that the warningspeed range has been installed
//asking if user wants to reinstall? 
void Car::Reinstallwarningspeed() {
	system("cls");
	cout << "CAC MUC VAN TOC CANH BAO KHOANG CACH AN TOAN DA DUOC CAI DAT: ";
	Printarray(warning_speed_, 3);
	cout << endl;
	cout << "BAN CO MUON CAI DAT LAI CAC MUC VAN TOC CANH BAO KHOANG CACH AN TOAN KHONG? ";
	if (YNQuestion())
	{
		system("cls");
		Installwarningspeed();
		Reinstallwarningspeed();
	}
}

// display MENU
void Car::Menu() {
	system("cls");
	cout << "XIN CHAO ";
	Printarray(mscn_, MSCN_ARRAY_SIZE);
	cout << endl;
	while (power_on)
	{
		switch (screen_)
		{
		case Screen::kNPScreen:
			cout << "BAN DANG O TAY SO " << gear_ << "--TOC DO HIEN TAI: " << speed_ << endl;
			cout << "XIN MOI LUA CHON:\n1. P\n2. R\n3. N\n4. D\n0. POWER OFF\n" << endl;
			break;
		case Screen::kRDScreen:
			if (gear_ == 'D')
			{
				if (speed_ < warning_speed_[0])
				{
					cout << "BAN CHU Y GIU KHOANG CACH TOI THIEU LA 20M " << endl;
				}
				else if (speed_ < warning_speed_[1])
				{
					cout << "BAN CHU Y GIU KHOANG CACH TOI THIEU LA 55M " << endl;
				}
				else if (speed_ < warning_speed_[2])
				{
					cout << "BAN CHU Y GIU KHOANG CACH TOI THIEU LA 70M " << endl;
				}
				else
				{
					cout << "BAN CHU Y GIU KHOANG CACH TOI THIEU LA 100M " << endl;
				}
				if (speed_ > 60) cout << "TOC DO NGUY HIEM, BAN NEN GIAM TOC DO" << endl;
			}
			else
			{
				if (speed_ > 20) cout << "TOC DO NGUY HIEM, BAN NEN GIAM TOC DO" << endl;
			}
			cout << "BAN DANG O TAY SO " << gear_ << "--TOC DO HIEN TAI: " << speed_ << endl;
			cout << "MOI LUA CHON:\n1. TANG TOC\n2. GIAM TOC\n3. PHANH\n0. TRO VE MENU\n" << endl;
			break;
		}
		Handleselection();
	}
	cout << "DA TAT MAY, TAM BIET, HEN GAP LAI BAN LAN SAU" << endl;
}

//the function require user's choice and handle it
void Car::Handleselection() {
	switch (screen_)
	{
	case Car::Screen::kNPScreen:
		switch (Inputselection(5))
		{
		case 1:
			//P
			Setgear('P');
			screen_ = Screen::kNPScreen;
			break;
		case 2:
			//R
			Setgear('R');
			screen_ = Screen::kRDScreen;
			break;
		case 3:
			//N
			Setgear('N');
			screen_ = Screen::kNPScreen;
			break;
		case 4:
			//D
			Setgear('D');
			screen_ = Screen::kRDScreen;
			break;
		case 0:
			//POWER OFF
			power_on = false;
			break;
		}
		break;
	case Car::Screen::kRDScreen:
		switch (Inputselection(4))
		{
		case 1:
			// speed up
			Speedup();
			break;
		case 2:
			//speed down
			Speeddown();
			break;
		case 3:
			//brake
			Brake();
			break;
		case 0:
			//back to the menu
			cout << "XIN CHAO ";
			Printarray(mscn_, MSCN_ARRAY_SIZE);
			cout << endl;
			screen_ = Screen::kNPScreen;
			break;
		}
		cout << endl;
		break;
	}
}

// requiring user's choice
// parameter is the total of choice
// output is user's choice
unsigned int Car::Inputselection(unsigned int sum_of_choice) {
	cout << "-->LUA CHON CUA BAN: ";
	string temp = "";
	getline(cin, temp);
	while (!Isunsignedinterger(temp) || stoi(temp) > sum_of_choice - 1)
	{
		cout << "LUA CHON KHONG HOP LE, VUI LONG LUA CHON LAI: ";
		getline(cin, temp);
	}
	system("cls");
	return stoi(temp);
}

//set up thee gear box
void Car::Setgear(char new_gear) {
	switch (new_gear) {
	case 'P':
		if (speed_ == 0) {
			gear_ = 'P';
			cout << "DA VE SO P.\nCHU Y SU DUNG PHANH TAY DE DAM BAO AN TOAN" << endl;
		}
		else
		{
			cout << "HAY CHAC CHAN XE DA DUNG(TOC DO 0 KM / H)" << endl;
		}
		break;
	case 'N':
		if (speed_ == 0) {
			gear_ = 'N';
			cout << "DA VE SO N." << endl;
		}
		else
		{
			cout << "HAY CHAC CHAN XE DA DUNG(TOC DO 0 KM / H)" << endl;
		}
		break;
	case 'D':
		if (gear_ != 'D') {
			if (speed_ == 0) {
				gear_ = 'D';
				speed_ = 7;
			}
			else {
				cout << "KHONG THE CHUYEN TU SO R SANG D KHI XE CHUA DUNG HAN(V = 0KM/H)!";
			}
		}
		break;
	case 'R':
		if (gear_ != 'R') {
			if (speed_ == 0) {
				gear_ = 'R';
				speed_ = 7;
			}
			else {
				cout << "KHONG THE CHUYEN TU SO D SANG R KHI XE CHUA DUNG HAN(V = 0KM/H)!";
			}
		}
		break;
	}
	cout << endl;
}

void Car::Speedup()
{
	speed_ += 5;
}

void Car::Speeddown()
{
	speed_ = (speed_ > 5) ? (speed_ - 5) : 0;
}

void Car::Brake()
{
	speed_ = 0;
}

bool Car::ReadData(string filename)
{
	ifstream file;
	file.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		file.open(filename, ios::binary);
		file.read((char*)this, sizeof(Car));
		return true;
	}
	catch (const ifstream::failure& e)
	{
		/*system("cls");
		cout << "--> Failed to read data from the file" << endl;
		cout << e.what() << endl;
		system("pause");
		system("cls");*/
	}
	catch (...)
	{
		/*system("cls");
		cout << "--> Failed to read data from the file" << endl;
		system("pause");
		system("cls");*/
	}
	return false;
}

void Car::WriteData(string filename)
{
	ofstream file;
	file.exceptions(ofstream::failbit | ofstream::badbit);
	try
	{
		file.open(filename, ios::binary);
		file.write((char*)this, sizeof(Car));
	}
	catch (...)
	{
		/*system("cls");
		cout << "--> Failed to write data to the file" << endl;
		system("pause");
		system("cls");*/
	}
}
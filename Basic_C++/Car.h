#ifndef CAR_H_
#define CAR_H_

//the size of private id array
#define MSCN_ARRAY_SIZE 8

#include <string>
using namespace std;

class Car
{
public:
	Car();
	void Run(string datefile);
private:
	//the private data of class include: private id,velocity to anounce safe distance
	unsigned int mscn_[MSCN_ARRAY_SIZE];
	unsigned int warning_speed_[3];

	enum class Screen
	{
		kNPScreen, kRDScreen
	};
	static unsigned int input_mscn_[];
	static bool power_on;
	static char gear_;
	static Screen screen_;
	static unsigned int speed_;

	bool Loginandsetup(string datafile);
	void InputMSCN();
	bool CheckMSCN();
	void ReinstallMSCN();
	void Installwarningspeed();
	void Reinstallwarningspeed();

	void Menu();
	void Handleselection();
	unsigned int Inputselection(unsigned int sum_of_choice);
	void Setgear(char new_gear);
	void Speedup();
	void Speeddown();
	void Brake();

	bool ReadData(string dataFile);
	void WriteData(string dataFile);

};

#endif // !CAR_H_

#include <Subsystems/Log.h>
#include "Drive.h"
#include "../RobotMap.h"
#include <WPILib.h>
#include <fstream>
#include <ctime>
#include <time.h>
#include <PowerDistributionPanel.h>

using namespace std;

ofstream outText;
frc::PowerDistributionPanel board;
int counter;

Log::Log() : Subsystem("Drive") {

}

//string Log::dateAndTime() {



//}

string Log::RandomNum() {

	srand (time(NULL));
	int num = rand()%10000;
	string numString = to_string(num);

	return numString;

}

void Log::Create() {

	//MUST PUT USB IN PORT ON INSIDE OF ROBORIO

	//late incorporate time and date and USB file path
	string filepath = "/u/" + RandomNum() + ".csv";
	outText.open(filepath);
	//outText.open("/u/test.txt");

}

void Log::Write(string text) {

	outText << text;
	outText << endl;

}

void Log::PDP(int slot, double limit, bool override) {

	double val = board.GetCurrent(slot);

	if(val > limit || override){
	string output = /*dateAndTime() + "," + */to_string(slot) + "," + to_string(limit) + "," + to_string(val) + "," + to_string(override);


	Write(output);
	}


}

void Log::PDPTotal(){
	double val = board.GetTotalCurrent();
	bool light;

	if (val > 1){
		counter = counter + 1;
		if (counter > 50){
			light = true;
		}
		else{
			light = false;
		}
	}
	else {
		counter = 0;
		light = false;
	}

	frc::SmartDashboard::PutBoolean("!! OVER 400 AMPS !!", light);
	auto Gyrooutstr = std::to_string(counter);
	frc::SmartDashboard::PutString("DB/String 5",Gyrooutstr);
}

void Log::DrivetrainCurrentCompare(int slot,double PWMin){

	double current = board.GetCurrent(slot);

	if (abs(PWMin) > .2){
		if (abs(current) < 1){
			string output = "!----PDP Slot" + to_string(slot) + "is not getting enough current when driven";
			Write(output);
			frc::SmartDashboard::PutString("Slot Not Getting Current",to_string(slot));
		}
	}
}

void Log::Close() {

	outText.close();

}

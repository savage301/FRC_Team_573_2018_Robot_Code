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

Log::Log() : Subsystem("Drive") {

}

string Log::dateAndTime() {



}

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

	string output = /*dateAndTime() + "," + */to_string(slot) + "," + to_string(limit) + "," + to_string(val) + "," + to_string(override);

	Write(output);

}

void Log::Close() {

	outText.close();

}

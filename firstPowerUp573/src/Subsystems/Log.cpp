#include <Subsystems/Log.h>
#include "Drive.h"
#include "../RobotMap.h"
#include <WPILib.h>
#include <fstream>
#include <ctime>
#include <time.h>
#include <chrono>
#include <iostream>
#include <sstream>
#include <PowerDistributionPanel.h>

using namespace std;

ofstream outText;
frc::PowerDistributionPanel board;

Log::Log() : Subsystem("Drive") {

}

string Log::dateAndTime() {

	/*time_t curTime = time(nullptr);
	string timeOut = asctime(localtime(&curTime));

	//return timeOut;

	return "test value";*/

	time_t t = time(0);
	struct tm * now = localtime(&t);

	int year = now->tm_year + 1900;
	string yearS = to_string(year);
	int month = now->tm_mon + 1;
	string monthS = to_string(month);
	int day = now->tm_mday;
	string dayS = to_string(day);
	int hour = now->tm_hour;
	string hourS = to_string(hour);
	int minute = now->tm_min;
	string minuteS = to_string(minute);
	int second = now->tm_sec;
	string secondS = to_string(second);

	string currentTimeDate = monthS + "." + dayS + "." + yearS + "___" + hourS + "." + minuteS + "." + secondS;

	return currentTimeDate;

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
	string filepath = "/u/" + dateAndTime() + ".txt";
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
	string output = dateAndTime() + "," + to_string(slot) + "," + to_string(limit) + "," + to_string(val) + "," + to_string(override);

	Write(output);
}


}

void Log::Close() {

	outText.close();

}

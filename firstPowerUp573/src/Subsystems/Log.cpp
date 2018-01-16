#include <Subsystems/Log.h>
#include "Drive.h"
#include "../RobotMap.h"
#include <WPILib.h>
#include <fstream>
#include <ctime>
#include <time.h>

using namespace std;

ofstream outText;

Log::Log() : Subsystem("Drive") {

}

string Log::dateAndTime() {

	time_t curTime = time(0);
	struct tm time;
	time = *localtime(&curTime);
	char buf[80];

	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &time);

	return buf;

}

void Log::Create() {

	//late incorporate time and date and USB file path
	outText.open("filename.txt");

}

void Log::Write(string text) {

	outText << text << "\n";

}

void Log::PDP(int slot, double limit, double val, bool override) {

	string output = dateAndTime() + "," + slot + "," + limit "," + val + "," + override;

	Write(output);

}

void Log::Close() {

	outText.close();

}

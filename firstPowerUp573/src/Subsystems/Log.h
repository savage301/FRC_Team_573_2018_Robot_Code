#ifndef Log_H
#define Log_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
using namespace std;

class Log : public Subsystem {


private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	Log();
	//string dateAndTime();
	void Create();
	string RandomNum();
	void PDP(int slot, double limit, bool override);
	void Write(string text);
	void Close();
};

#endif  // Drive_H

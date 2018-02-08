#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

using namespace std;

class Autonomous : public Subsystem {


private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	Autonomous();
	int ModeSelect();
	void CrossLine(int counter);

};

#endif  // AUTONOMOUS_H

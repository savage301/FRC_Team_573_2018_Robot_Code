#ifndef Drive_H
#define Drive_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
using namespace std;

class Drive : public Subsystem {


private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
Talon * LeftDrive;
Talon * RightDrive;


public:
	Drive();
	void InitDefaultCommand();
	void TankDrive(double left, double right);
	void CameraCenter(double y);
};

#endif  // Drive_H

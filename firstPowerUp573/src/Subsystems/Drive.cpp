#include "Drive.h"
#include "../RobotMap.h"
#include <WPILib.h>


using namespace std;
Drive::Drive() : Subsystem("Drive") {

	// Setup Motor Controllers
	LeftDrive = new Talon(LeftDrivePWM);
	RightDrive = new Talon(RightDrivePWM);


}

void Drive::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drive::TankDrive(double left, double right) {

	LeftDrive->Set(left); //Set left value to left drive
	RightDrive->Set(right); //Set right value to right drive

}


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

void Drive::CameraCenter(double y) {

	double PIDTurn;

	//------------------------ vision read-in -----------------------------

	std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
	float targetOffsetAngle_Horizontal = table->GetNumber("tx",0);
	float targetOffsetAngle_Vertical = table->GetNumber("ty",0);
	float targetArea = table->GetNumber("ta",0);
	float targetSkew = table->GetNumber("ts",0);
	float targetExists = table->GetNumber("tv",0);

	table->PutNumber("ledMode",-1);
	table->PutNumber("pipeline",-4);



	RobotDrive::ArcadeDrive(y, PIDTurn, true);

}


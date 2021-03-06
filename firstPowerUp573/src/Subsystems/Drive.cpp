#include "Drive.h"
#include "../RobotMap.h"
#include <WPILib.h>
#include "RobotDrive.h"
#include <ADXRS450_Gyro.h>
#include <Encoder.h>

using namespace std;

double leftdriveold;
double rightdriveold;

Drive::Drive() : Subsystem("Drive") {

	// Setup Motor Controllers
	LeftDrive = new Talon(LeftDrivePWM);
	RightDrive = new Talon(RightDrivePWM);
	MyGyro = new ADXRS450_Gyro();
	LeftDriveEncoder = new Encoder(0, 1, false, Encoder::k4X);
	RightDriveEncoder = new Encoder(2, 3, false, Encoder::k4X);
	Shifter = new DoubleSolenoid(PCM, ShifterPort1, ShifterPort2);
	LeftDrive->SetInverted(true);


}

void Drive::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drive::TankDrive(double left, double right) {

	if (left > leftdriveold + .3){

		left = (leftdriveold + .3);

	}

	else if (left < leftdriveold - .3){

		left = (leftdriveold - .3);

	}

	if (right > rightdriveold + .3){

		right = (rightdriveold + .3);

	}

	else if (right < rightdriveold - .3){

		right = (rightdriveold - .3);

	}


	LeftDrive->Set(left); //Set left value to left drive
	RightDrive->Set(right); //Set right value to right drive

	leftdriveold = left;
	rightdriveold = right;
}

void Drive::CameraCenter(double y) {

	//------------------------ vision read-in -----------------------------

	std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
	table->PutNumber("ledMode",1);
	table->PutNumber("pipeline",4);

	float targetOffsetAngle_Horizontal = table->GetNumber("tx",0);
	float targetOffsetAngle_Vertical = table->GetNumber("ty",0);
	float targetArea = table->GetNumber("ta",0);
	float targetSkew = table->GetNumber("ts",0);
	float targetExists = table->GetNumber("tv",0);

	frc::SmartDashboard::PutNumber("tx Cam", targetOffsetAngle_Horizontal);
	frc::SmartDashboard::PutNumber("ty Cam", targetOffsetAngle_Vertical);
	frc::SmartDashboard::PutNumber("ta Cam", targetArea);
	frc::SmartDashboard::PutNumber("ts Cam", targetSkew);
	frc::SmartDashboard::PutNumber("tv Cam", targetExists);

	//Hardcoded P function
	double PIDTurn;
	double xError = 0 - targetOffsetAngle_Horizontal;
	double kP = 0.025;
	PIDTurn = kP * xError;

	if(PIDTurn > .8) {

		PIDTurn = .8;

	} else if(PIDTurn < -.8) {

		PIDTurn = -.8;

	}

	//Hardcoding arcade drive with y and pivot axes
	double leftPower = (y + PIDTurn);
	double rightPower = (y - PIDTurn);

	LeftDrive->Set(leftPower); //Set left value to left drive
	RightDrive->Set(rightPower); //Set right value to right drive

}

void Drive::GyroSetpoint(double degrees) {

	double gyroCurrent = MyGyro->GetAngle();
	double gyroError = degrees - gyroCurrent;
	double PIDTurn;
	double kP = -0.015;
	PIDTurn = kP * gyroError;

	frc::SmartDashboard::PutString("DB/String 1", to_string(gyroCurrent));

	if(PIDTurn > .8) {

		PIDTurn = .8;

	} else if(PIDTurn < -.8) {

		PIDTurn = -.8;

	}

	//Hardcoding arcade drive with y and pivot axes
	double leftPower = PIDTurn;
	double rightPower = -1 * PIDTurn;

	LeftDrive->Set(leftPower); //Set left value to left drive
	RightDrive->Set(rightPower); //Set right value to right drive

}

void Drive::EncoderSetpoint(double setpoint) {

	//Wheel moves 2.17 inches per motor revolution
	//Calculating distance covered by robot through encoder

	double leftEncoderVal = LeftDriveEncoder->Get();
	double rightEncoderVal = RightDriveEncoder->Get();

	double leftDistance = leftEncoderVal * 5 / 963;
	frc::SmartDashboard::PutString("DB/String 2", to_string(leftDistance));
	double rightDistance = rightEncoderVal * 5 / 963;
	frc::SmartDashboard::PutString("DB/String 3", to_string(rightEncoderVal));
	//double avgDistance = (leftDistance + rightDistance) / 2;
	double avgDistance = rightDistance;

	double distanceError = setpoint - avgDistance;
	double kPEncoder = -0.4;
	double output = kPEncoder * distanceError;

	if(output > .75) {

		output = .75;

	} else if(output < -.75) {

		output = -.75;

	}

	//------------------- Gyro stabilization -------------------------------

	double gyroCurrent = MyGyro->GetAngle();
	double gyroError = 0 - gyroCurrent;
	double kPGyro = -0.04;
	double PIDTurn = kPGyro * gyroError;

	frc::SmartDashboard::PutString("DB/String 4", to_string(gyroCurrent));

	if(PIDTurn > .5) {

		PIDTurn = .5;

	} else if(PIDTurn < -.5) {

		PIDTurn = -.5;

	}

	//Hardcoding arcade drive with y and pivot axes
	double leftPower = output + PIDTurn;
	double rightPower = output - PIDTurn;

	if (leftPower > .9){
		leftPower = .9;
	}
	else if (leftPower < -.9){
		leftPower = -.9;
	}

	if (rightPower > .9){
		rightPower = .9;
	}
	else if (rightPower < -.9){
		rightPower = -.9;
	}
	LeftDrive->Set(leftPower); //Set left value to left drive
	RightDrive->Set(rightPower); //Set right value to right drive

}

void Drive::EncoderReset() {
 //double blah;
	LeftDriveEncoder->Reset();
	RightDriveEncoder->Reset();


}

void Drive::GyroReset() {

	MyGyro->Reset();

}

void Drive::ProgrammingTabInfoDrive(){
	//Must move inside a function in Drive.cpp
	double gyroval = MyGyro->GetAngle();
	frc::SmartDashboard::PutString("Gyro", to_string(gyroval));

	double leftenc = LeftDriveEncoder->Get();
	frc::SmartDashboard::PutString("Drive Encoder Left", to_string(leftenc));

	double rightenc = RightDriveEncoder->Get();
	frc::SmartDashboard::PutString("Drive Encoder Right", to_string(rightenc));

	std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
	table->PutNumber("ledMode",1);
	table->PutNumber("pipeline",4);
	float targetOffsetAngle_Horizontal = table->GetNumber("tx",0);
	float targetOffsetAngle_Vertical = table->GetNumber("ty",0);
	float targetArea = table->GetNumber("ta",0);
	float targetSkew = table->GetNumber("ts",0);
	float targetExists = table->GetNumber("tv",0);

	frc::SmartDashboard::PutNumber("tx Cam", targetOffsetAngle_Horizontal);
	frc::SmartDashboard::PutNumber("ty Cam", targetOffsetAngle_Vertical);
	frc::SmartDashboard::PutNumber("ta Cam", targetArea);
	frc::SmartDashboard::PutNumber("ts Cam", targetSkew);
	frc::SmartDashboard::PutNumber("tv Cam", targetExists);

	auto ShifterStatus = Shifter->Get();
	bool ShiftStatusInd;

	string ShiftStatusStr = to_string(ShifterStatus);
	if (ShiftStatusStr == "2"){
		ShiftStatusInd = true;
	}
	else{
		ShiftStatusInd = false;
	}
	frc::SmartDashboard::PutString("DB/String 4",to_string(ShifterStatus));

	frc::SmartDashboard::PutBoolean("High-gear (on) / Low-gear (off)",ShiftStatusInd);

}

void Drive::Booster(bool button){
	if (button){
		Shifter->Set(DoubleSolenoid::Value::kReverse);
	}
	else {
		Shifter->Set(DoubleSolenoid::Value::kForward);
	}
}

void Drive::StraightGyro(double y) {


	//Hardcoded P function
	double gyroCurrent = MyGyro->GetAngle();
	double gyroError = 0 - gyroCurrent;
	double kPGyro = -0.04;
	double PIDTurn = kPGyro * gyroError;


	if(PIDTurn > .8) {

		PIDTurn = .8;

	} else if(PIDTurn < -.8) {

		PIDTurn = -.8;

	}

	if(y > .75) {

	y = .75;

	} else if(y < -.75) {

	y = -.75;

	}

	//Hardcoding arcade drive with y and pivot axes
	double leftPower = (y + PIDTurn);
	double rightPower = (y - PIDTurn);

	if (leftPower > .9){
		leftPower = .9;
	}
	else if (leftPower < -.9){
		leftPower = -.9;
	}

	if (rightPower > .9){
		rightPower = .9;
	}
	else if (rightPower < -.9){
		rightPower = -.9;
	}
	LeftDrive->Set(leftPower); //Set left value to left drive
	RightDrive->Set(rightPower); //Set right value to right drive

}

void Drive::EncoderSetpointNonZeroGyro(double setpoint, double gyrosetpoint) {

	//Wheel moves 2.17 inches per motor revolution
	//Calculating distance covered by robot through encoder

	double leftEncoderVal = LeftDriveEncoder->Get();
	double rightEncoderVal = RightDriveEncoder->Get();

	double leftDistance = leftEncoderVal * 5 / 963;
	frc::SmartDashboard::PutString("DB/String 2", to_string(leftDistance));
	double rightDistance = rightEncoderVal * 5 / 963;
	frc::SmartDashboard::PutString("DB/String 3", to_string(rightEncoderVal));
	//double avgDistance = (leftDistance + rightDistance) / 2;
	double avgDistance = rightDistance;

	double distanceError = setpoint - avgDistance;
	double kPEncoder = -0.4;
	double output = kPEncoder * distanceError;

	if(output > .75) {

		output = .75;

	} else if(output < -.75) {

		output = -.75;

	}

	//------------------- Gyro stabilization -------------------------------

	double gyroCurrent = MyGyro->GetAngle();
	double gyroError = gyrosetpoint - gyroCurrent;
	double kPGyro = -0.04;
	double PIDTurn = kPGyro * gyroError;

	frc::SmartDashboard::PutString("DB/String 4", to_string(gyroCurrent));

	if(PIDTurn > .5) {

		PIDTurn = .5;

	} else if(PIDTurn < -.5) {

		PIDTurn = -.5;

	}

	//Hardcoding arcade drive with y and pivot axes
	double leftPower = output + PIDTurn;
	double rightPower = output - PIDTurn;

	if (leftPower > .9){
		leftPower = .9;
	}
	else if (leftPower < -.9){
		leftPower = -.9;
	}

	if (rightPower > .9){
		rightPower = .9;
	}
	else if (rightPower < -.9){
		rightPower = -.9;
	}
	LeftDrive->Set(leftPower); //Set left value to left drive
	RightDrive->Set(rightPower); //Set right value to right drive

}


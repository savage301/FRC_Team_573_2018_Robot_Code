#ifndef Drive_H
#define Drive_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <Encoder.h>
using namespace std;

class Drive : public Subsystem {


private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
Talon * LeftDrive;
Talon * RightDrive;
//RobotDrive * MyRobotDrive;



public:
	Drive();
	void InitDefaultCommand();
	void TankDrive(double left, double right);
	void CameraCenter(double y);
	void GyroSetpoint(double degrees);
	void GyroReset();
	void EncoderSetpoint(double setpoint);
	void EncoderReset();
	ADXRS450_Gyro * MyGyro;
	Encoder * LeftDriveEncoder;
	Encoder * RightDriveEncoder;

};

#endif  // Drive_H

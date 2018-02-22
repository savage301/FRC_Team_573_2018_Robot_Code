#ifndef Appendage_H
#define Appendage_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <Encoder.h>
using namespace std;

class Appendage : public Subsystem {


private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
Talon * ClawMotorLeft1;

Talon * ClawMotorRight1;


Talon * Elevator1;
Talon * Elevator2;

DoubleSolenoid * Brake;

DoubleSolenoid * Ramp1;

DigitalInput * Boxlightgate;

Encoder * ElevatorEncoder;

AnalogInput * Ultrasonic;

Talon * RampLeft;
Talon * RampRight;




void ElevPID(double POS);
public:
Appendage();
	void InitDefaultCommand();
	void Claw(double speed);
	void Elevator(double Joystick, bool a, bool b, bool x, bool y);
	void Ramp(bool Button1,bool btnleft, bool btnright,bool rampup1,bool rampup2);
	bool LightGateGet();
	double GetDistanceUltrasonic();
	void ProgrammingTabInfoAppendage();
	void EncoderReset();


};


#endif  // Appendage_H

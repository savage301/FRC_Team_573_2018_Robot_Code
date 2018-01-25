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
DoubleSolenoid * Ramp2;

DigitalInput * Boxlightgate;

Encoder * ElevatorEncoder;




void ElevPID(double POS);
public:
Appendage();
	void InitDefaultCommand();
	void Claw(double speed);
	void Elevator(double Joystick, bool a, bool b, bool x, bool y);
	void Ramp(bool Button1);
	void LightGateGet();

};


#endif  // Appendage_H

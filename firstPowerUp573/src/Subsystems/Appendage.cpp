#include "Appendage.h"
#include "../RobotMap.h"
#include <WPILib.h>
#include <cmath>



using namespace std;
Appendage::Appendage() : Subsystem("Appendage") {

	// Setup Motor Controllers
	ClawMotorLeft1 = new Talon(ClawMotorLeft1PWM);
	ClawMotorLeft2 = new Talon(ClawMotorLeft2PWM);
	ClawMotorRight1 = new Talon(ClawMotorRight1PWM);
	ClawMotorRight2 = new Talon(ClawMotorRight2PWM);

	Elevator1 = new Talon(ElevatorPWM);
	Elevator2 = new Talon(ElevatorPWM);
	Brake = new DoubleSolenoid(PCM, BrakePort1, BrakePort2);
	Ramp1 = new DoubleSolenoid(PCM, Ramp1Port1, Ramp1Port2);
	Ramp2 = new DoubleSolenoid(PCM, Ramp2Port1, Ramp2Port2);


}

void Appendage::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Appendage::Claw(double speed) {

	ClawMotorLeft1->Set(speed); //Set left value to talon
	ClawMotorLeft2->Set(speed); //Set left value to talon
	ClawMotorRight1->Set(speed); //Set left value to talon
	ClawMotorRight2->Set(speed); //Set left value to talon

}
void Appendage::Elevator(double Joystick, bool a, bool b, bool x, bool y){

	double absJoystick = abs(Joystick);
	if (absJoystick > .25){
		Elevator1->Set(Joystick);
		Elevator2->Set(Joystick);
		Brake->Set(DoubleSolenoid::Value::kReverse);
	}
	else {
		Elevator1->Set(0);
		Elevator2->Set(0);
		Brake->Set(DoubleSolenoid::Value::kForward);
	}

}

void Appendage::Ramp(bool Button1){
	if (Button1){
		Ramp1->Set(DoubleSolenoid::Value::kForward);
		Ramp2->Set(DoubleSolenoid::Value::kForward);
	}
	else {
		Ramp1->Set(DoubleSolenoid::Value::kReverse);
		Ramp2->Set(DoubleSolenoid::Value::kReverse);
	}
}


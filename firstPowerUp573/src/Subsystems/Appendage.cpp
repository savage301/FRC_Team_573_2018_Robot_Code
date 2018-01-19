#include "Appendage.h"
#include "../RobotMap.h"
#include <WPILib.h>
#include <cmath>
#include <Encoder.h>



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
	Boxlightgate = new DigitalInput(BoxlightgateDIO);
	ElevatorEncoder = new Encoder(ElevatorEncoder1, ElevatorEncoder2, false, Encoder::k4X);


}

void Appendage::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Appendage::Claw(double speed) {


	if (speed <= 0){
		ClawMotorLeft1->Set(speed); //Set left value to talon
		ClawMotorLeft2->Set(speed); //Set left value to talon
		ClawMotorRight1->Set(speed); //Set left value to talon
		ClawMotorRight2->Set(speed); //Set left value to talon
	}
	else if (speed > 0 and Boxlightgate->Get()){
		ClawMotorLeft1->Set(speed); //Set left value to talon
		ClawMotorLeft2->Set(speed); //Set left value to talon
		ClawMotorRight1->Set(speed); //Set left value to talon
		ClawMotorRight2->Set(speed); //Set left value to talon
	}
	else {
		ClawMotorLeft1->Set(0); //Set left value to talon
		ClawMotorLeft2->Set(0); //Set left value to talon
		ClawMotorRight1->Set(0); //Set left value to talon
		ClawMotorRight2->Set(0); //Set left value to talon
	}



}
void Appendage::Elevator(double Joystick, bool a, bool b, bool x, bool y){

	double PosA = 0;
	double PosB = 30;
	double PosX = 50;
	double PosY = 70;
	//double Encodererror;
	double absJoystick = abs(Joystick);





		//double Encodererror;

	if (a){
		ElevPID(PosA);
	}
	else if (b){
		ElevPID(PosB);
	}
	else if (x){
		ElevPID(PosX);
	}
	else if (y){
		ElevPID(PosY);
	}
	else if (absJoystick > .25){
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

void Appendage::ElevPID(double POS){

	double EncoderDistance = ElevatorEncoder->GetDistance();
	auto Gyrooutstr = std::to_string(EncoderDistance);
	frc::SmartDashboard::PutString("DB/String 0",Gyrooutstr);
	double Kp = -0.04;

	double Encodererror = POS - EncoderDistance;
	auto Gyrooutstr1 = std::to_string(Encodererror);
	frc::SmartDashboard::PutString("DB/String 1",Gyrooutstr1);
		if (abs (Encodererror) < 0.5){
				Elevator1->Set(0);
				Elevator2->Set(0);
				Brake->Set(DoubleSolenoid::Value::kForward);
			}
		else {
				Elevator1->Set(Kp*Encodererror);
				Elevator2->Set(Kp*Encodererror);
				Brake->Set(DoubleSolenoid::Value::kReverse);
			}

}

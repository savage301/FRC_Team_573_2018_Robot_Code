#include "Appendage.h"
#include "../RobotMap.h"
#include <WPILib.h>
#include <cmath>
#include <Encoder.h>
#include <Relay.h>



using namespace std;
Appendage::Appendage() : Subsystem("Appendage") {

	// Setup Motor Controllers
	ClawMotorLeft1 = new Talon(ClawMotorLeft1PWM);

	ClawMotorRight1 = new Talon(ClawMotorRight1PWM);


	Elevator1 = new Talon(ElevatorPWM);
	Elevator2 = new Talon(ElevatorPWM);
	Brake = new DoubleSolenoid(PCM, BrakePort1, BrakePort2);
	//Ramp1 = new DoubleSolenoid(PCM, Ramp1Port1, Ramp1Port2);
	ClawWristSol = new DoubleSolenoid(PCM,ClawWristPort1,ClawWristPort1);
	ClimberSol = new DoubleSolenoid(PCM,ClimberPort1,ClimberPort2);

	Boxlightgate = new DigitalInput(BoxlightgateDIO);
	ElevatorEncoder = new Encoder(ElevatorEncoder1, ElevatorEncoder2, false, Encoder::k4X);
	Ultrasonic = new AnalogInput(UltrasonicPort);

	RampLeft = new Talon(RampLeftPWM);
	RampRight = new Talon(RampRightPWM);

	WhiteLED = new Relay(2,Relay::kBothDirections);
	AmberLED = new Relay(0,Relay::kBothDirections);


}

void Appendage::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Appendage::LightGateGet(){
	bool lightgatebool = not(Boxlightgate->Get());

	auto Gyrooutstr = std::to_string(lightgatebool);
	frc::SmartDashboard::PutString("DB/String 6",Gyrooutstr);

	frc::SmartDashboard::PutBoolean("Box in Robot", lightgatebool);

	return lightgatebool;
}


void Appendage::Claw(double speed) {

	double EncoderDistanceCheck = ElevatorEncoder->GetDistance();
	if (speed < 0){

		if(EncoderDistanceCheck>2200){
			ClawMotorRight1->Set(-0.4); //Set left value to talon
			ClawMotorLeft1->Set(0.4); //Set left value to talon
		}
		else{
			ClawMotorRight1->Set(speed); //Set left value to talon
			double invspeed = (-1)*speed;
			ClawMotorLeft1->Set(invspeed); //Set left value to talon
		}

	}
	else if (speed > 0){ //and Boxlightgate->Get()){ Removed lightgate for stopping intake on claw
		if(EncoderDistanceCheck>2200){
			ClawMotorRight1->Set(0.4); //Set left value to talon
			ClawMotorLeft1->Set(-0.4); //Set left value to talon
		}
		else{
		ClawMotorRight1->Set(speed); //Set left value to talon
		double invspeed = (-1)*speed;
		ClawMotorLeft1->Set(invspeed); //Set left value to talon
		}
	}
	else {
		ClawMotorLeft1->Set(0); //Set left value to talon
		ClawMotorRight1->Set(0); //Set left value to talon

	}



}
void Appendage::Elevator(double Joystick, bool a, bool b, bool x, bool y){

	double PosA = 0;  //Encoder values for elevator must be updated if drum diameter changes
	double PosB = 3860;
	double PosX = 8200;
	double PosY = 8200;
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
	else if (absJoystick > .75){
		if (Joystick > 0){
			Elevator1->Set(.75);
			Elevator2->Set(.75);
			Brake->Set(DoubleSolenoid::Value::kReverse);
		}
		else{
		Elevator1->Set(Joystick);
		Elevator2->Set(Joystick);
		Brake->Set(DoubleSolenoid::Value::kReverse);
		}

	}
	else {
		Elevator1->Set(0);
		Elevator2->Set(0);
		Brake->Set(DoubleSolenoid::Value::kForward);
	}




}
/*
void Appendage::Ramp(bool Button1,bool btnleft, bool btnright,bool rampup1,bool rampup2){
	if (Button1){
		Ramp1->Set(DoubleSolenoid::Value::kForward);
		if (btnleft){
			RampLeft->Set(1);
		}
		else if(rampup1){
			RampLeft->Set(-.75);
		}
		else{
			RampLeft->Set(0);
		}
		if (btnright){
			RampRight->Set(1);
		}
		else if (rampup2){
			RampRight->Set(-.75);
		}
		else{
			RampRight->Set(0);
		}
	}

	else {
		Ramp1->Set(DoubleSolenoid::Value::kReverse);
		RampLeft->Set(0);
		RampRight->Set(0);
	}
}
*/
void Appendage::ElevPID(double POS){

	double EncoderDistance = ElevatorEncoder->GetDistance();
	auto Gyrooutstr = std::to_string(EncoderDistance);
	frc::SmartDashboard::PutString("DB/String 0",Gyrooutstr);
	double Kp = -0.001;

	double Encodererror = POS - EncoderDistance;
	auto Gyrooutstr1 = std::to_string(Encodererror);
	frc::SmartDashboard::PutString("DB/String 1",Gyrooutstr1);
		if (abs (Encodererror) < 100){
				Elevator1->Set(0);
				Elevator2->Set(0);
				Brake->Set(DoubleSolenoid::Value::kForward);
			}
		else {
		if (Kp*Encodererror >.5){
			Elevator1->Set(.5);
			Elevator2->Set(.5);
			Brake->Set(DoubleSolenoid::Value::kReverse);
		}
		else{
			Elevator1->Set(Kp*Encodererror);
				Elevator2->Set(Kp*Encodererror);
				Brake->Set(DoubleSolenoid::Value::kReverse);
			}
		}

}

double Appendage::GetDistanceUltrasonic(){
	double val = Ultrasonic->GetVoltage(); //Get distance form range finder
	double distval = 8.8342*val+0.279; //Converting "val" from volts to feet
	frc::SmartDashboard::PutString("DB/String 9", to_string(distval)); //Sends "distval" to the dashboard

	double EncoderDistance = ElevatorEncoder->GetDistance();
	double UltrasonicEncoder = EncoderDistance-distval; //Reads the height of the object in the view of the ultrasonic sensor

	bool ObjectDetected;
	if (UltrasonicEncoder > 1){
		ObjectDetected = true; //if the object is more then a foot tall, then [true]
	}
	else{
		ObjectDetected = false; //if not, then [false]
	}

 return distval;
}


void Appendage::ProgrammingTabInfoAppendage(){

	double val;
	val = GetDistanceUltrasonic();
	frc::SmartDashboard::PutString("Raw Distance Sensor", to_string(val));

	val = ElevatorEncoder->GetDistance();
	frc::SmartDashboard::PutString("Lift Encoder", to_string(val));

}

void Appendage::EncoderReset() {
 //double blah;
	ElevatorEncoder->Reset();



}

void Appendage::ClawWrist(bool ButtonUp, bool ButtonDown){

	if (ButtonUp){
		ClawWristSol->Set(DoubleSolenoid::Value::kForward);
	}
	else if (ButtonDown){
		ClawWristSol->Set(DoubleSolenoid::Value::kReverse);
	}


}

void Appendage::Climber(bool DropForks){

	if (DropForks){
		ClimberSol->Set(DoubleSolenoid::Value::kForward);
		}
	else{
		ClimberSol->Set(DoubleSolenoid::Value::kReverse);
	}
}

void Appendage::LEDs(bool btn1, bool btn2){

	if (btn1){
	WhiteLED->Set(Relay::Value::kForward);
	}
	else{
	WhiteLED->Set(Relay::Value::kOff);
	}
	if(btn2){
	AmberLED->Set(Relay::Value::kForward);
	}
	else{
	AmberLED->Set(Relay::Value::kOff);
	}

}

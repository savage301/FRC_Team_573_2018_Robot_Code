#include "Appendage.h"
#include "../RobotMap.h"
#include <WPILib.h>
#include <cmath>
#include <Encoder.h>



using namespace std;
Appendage::Appendage() : Subsystem("Appendage") {

	// Setup Motor Controllers
	ClawMotorLeft1 = new Talon(ClawMotorLeft1PWM);

	ClawMotorRight1 = new Talon(ClawMotorRight1PWM);


	Elevator1 = new Talon(ElevatorPWM);
	Elevator2 = new Talon(ElevatorPWM);
	Brake = new DoubleSolenoid(PCM, BrakePort1, BrakePort2);
	Ramp1 = new DoubleSolenoid(PCM, Ramp1Port1, Ramp1Port2);

	Boxlightgate = new DigitalInput(BoxlightgateDIO);
	ElevatorEncoder = new Encoder(ElevatorEncoder1, ElevatorEncoder2, false, Encoder::k4X);
	Ultrasonic = new AnalogInput(UltrasonicPort);


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


	if (speed <= 0){
		ClawMotorLeft1->Set(speed); //Set left value to talon
		double invspeed = (-1)*speed;
		ClawMotorRight1->Set(invspeed); //Set left value to talon

	}
	else if (speed > 0 and Boxlightgate->Get()){
		ClawMotorLeft1->Set(speed); //Set left value to talon
		double invspeed = (-1)*speed;
		ClawMotorRight1->Set(invspeed); //Set left value to talon

	}
	else {
		ClawMotorLeft1->Set(0); //Set left value to talon

		ClawMotorRight1->Set(0); //Set left value to talon

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

	}
	else {
		Ramp1->Set(DoubleSolenoid::Value::kReverse);

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

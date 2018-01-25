/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>
#include <WPILib.h>
#include <Joystick.h>
#include <Subsystems/Drive.h>
#include <Subsystems/Appendage.h>
#include <Subsystems/Autonomous.h>
#include "Commands/ExampleCommand.h"
#include "Commands/MyAutoCommand.h"
#include "RobotMap.h"
#include "NetworkTables/NetworkTable.h"
#include <iostream>
#include <Subsystems/Log.h>

class Robot : public frc::TimedRobot {
public:

	frc::Joystick controller1{ Driver1 };  // only joystick
	frc::Joystick controller2{ Driver2 };  // only joystick
	Drive MyDrive;
	Appendage MyAppendage;
	Log myLog;
	frc::PowerDistributionPanel board;
	Autonomous myAuto;




	void RobotInit() override {
		m_chooser.AddDefault("Default Auto", &m_defaultAuto);
		m_chooser.AddObject("My Auto", &m_myAuto);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

		//std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");

		//table->PutNumber("ledMode",1);

	}

	/**
	 * This function is called once each time the robot enters Disabled
	 * mode.
	 * You can use it to reset any subsystem information you want to clear
	 * when
	 * the robot is disabled.
	 */
	void DisabledInit() override {

		myLog.Close();

	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to
	 * select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to
	 * the
	 * chooser code above (like the commented example) or additional
	 * comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override {
		std::string autoSelected = frc::SmartDashboard::GetString(
				"Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			m_autonomousCommand = &m_myAuto;
		} else {
			m_autonomousCommand = &m_defaultAuto;
		}

		m_autonomousCommand = m_chooser.GetSelected();

		if (m_autonomousCommand != nullptr) {
			m_autonomousCommand->Start();
		}

		myAuto.ModeSelect();

	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (m_autonomousCommand != nullptr) {
			m_autonomousCommand->Cancel();
			m_autonomousCommand = nullptr;
		}

		myLog.Create();

	}

	void TeleopPeriodic() override {

		frc::Scheduler::GetInstance()->Run();
		MyAppendage.GetDistanceUltrasonic();

// -------------------- Logging Code ---------------------------------------------/
		//myLog.Write("Test Output");
		//myLog.PDP(15, 5, false);


// ---------------------------------------------------------------------------

// --------------- Basic Driving --------------------------------------

		double leftin = pow(controller1.GetRawAxis(1), 3); //Get Drive Left Joystick Y Axis Value
		double rightin = pow(controller1.GetRawAxis(5), 3); //Get Drive right Joystick Y Axis Value
		bool AButton = controller1.GetRawButton(1);
		bool BButton = controller1.GetRawButton(2);
		bool XButton = controller1.GetRawButton(3);
		bool YButton = controller1.GetRawButton(4);
		bool LBButton = controller1.GetRawButton(5);

// ------------------------------------------------------------------------------------------
// ------------Camera Aided Driving ----------------------

		if(AButton) {

			MyDrive.CameraCenter(leftin);

		} else if(BButton) {

			MyDrive.GyroSetpoint(90);

		} else if(YButton) {

			MyDrive.EncoderSetpoint(108);

		} else {

			MyDrive.TankDrive(leftin,rightin); //Pass to Tank Drive Function

		}


		if(XButton)
			MyDrive.GyroReset();

		if(LBButton)
			MyDrive.EncoderReset();




// ------------- Dashboard Indicator Code ---------------------------------
	//Total Current
		myLog.PDPTotal();

	//Box in Vision
		std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
		table->PutNumber("ledMode",1);
		table->PutNumber("pipeline",4);

		bool cubeBool;
		float targetExists = table->GetNumber("tv",0);
		if (targetExists == 1){
			cubeBool = true;
		}
		else {
			cubeBool = false;
		}

		frc::SmartDashboard::PutBoolean("Cube in Camview", cubeBool);

	//Box in Claw
		MyAppendage.LightGateGet();

	//Current Mismatch

		myLog.DrivetrainCurrentCompare(0,leftin);
		myLog.DrivetrainCurrentCompare(1,leftin);
		myLog.DrivetrainCurrentCompare(2,leftin);
		myLog.DrivetrainCurrentCompare(13,rightin);
		myLog.DrivetrainCurrentCompare(14,rightin);
		myLog.DrivetrainCurrentCompare(15,rightin);


		//

// ----------------------------Claw Control----------------------------
		double clawinraw = controller2.GetRawAxis(2);
		double clawoutraw = controller2.GetRawAxis(3);
		bool clawinbtn;
		bool clawoutbtn;

		//Taking the raw value and making it a boolean
		if (clawinraw > .75){
			clawinbtn = 1;
		}
		else {
			clawinbtn = 0;
		}

		if (clawoutraw > .75){
			clawoutbtn = 1;
		}
		else {
			clawoutbtn = 0;
		}

		//Setting talons
		if (clawinbtn){
			MyAppendage.Claw(.8);
		}
		else if (clawoutbtn){
			MyAppendage.Claw(-.8);
		}
		else {
			MyAppendage.Claw(0);
		}

// Random Logging code???
		myLog.PDP(1, 5, true);



//--------------------------------------------------------------------------------------

//---------------------------Elevator Code--------------------------------------------
		double elevatorraw = controller2.GetRawAxis(1);
		bool elevatorground = controller2.GetRawButton(1);
		bool elevatorpos1 = controller2.GetRawButton(2);
		bool elevatorpos2 = controller2.GetRawButton(3);
		bool elevatorpos3 = controller2.GetRawButton(4);

		MyAppendage.Elevator(elevatorraw, elevatorground, elevatorpos1, elevatorpos2, elevatorpos3);

//------------------------------------------------------------------------------------

//---------------------------Ramps-----------------------------
	bool rampbutton1 = controller2.GetRawButton(5);
	bool rampbutton2 = controller2.GetRawButton(6);
	bool rampbutton3 = controller2.GetRawButton(10);

	if (rampbutton1 && rampbutton2){
		rampcontrol = 1;
	}
	if (rampbutton3){
		rampcontrol = 0;
	}

	MyAppendage.Ramp(rampcontrol);


	}

//---------------------------------------------------------------------------------------


	void TestPeriodic() override {
	}

private:
	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command* m_autonomousCommand = nullptr;
	ExampleCommand m_defaultAuto;
	MyAutoCommand m_myAuto;
	frc::SendableChooser<frc::Command*> m_chooser;
	bool rampcontrol = 0;
};

START_ROBOT_CLASS(Robot)

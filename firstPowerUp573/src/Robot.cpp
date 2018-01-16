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
#include "Commands/ExampleCommand.h"
#include "Commands/MyAutoCommand.h"
#include "RobotMap.h"
#include "NetworkTables/NetworkTable.h"
#include <iostream>

class Robot : public frc::TimedRobot {
public:

	frc::Joystick controller1{ Driver1 };  // only joystick
	frc::Joystick controller2{ Driver2 };  // only joystick
	Drive MyDrive;
	Appendage MyAppendage;



	void RobotInit() override {
		m_chooser.AddDefault("Default Auto", &m_defaultAuto);
		m_chooser.AddObject("My Auto", &m_myAuto);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

	}

	/**
	 * This function is called once each time the robot enters Disabled
	 * mode.
	 * You can use it to reset any subsystem information you want to clear
	 * when
	 * the robot is disabled.
	 */
	void DisabledInit() override {


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
	}

	void TeleopPeriodic() override {

		frc::Scheduler::GetInstance()->Run();

// --------------- Teleop Joystick controlled driving --------------------------------------
		double leftin = controller1.GetRawAxis(1); //Get Drive Left Joystick Y Axis Value
		double rightin = controller1.GetRawAxis(5); //Get Drive right Joystick Y Axis Value
		MyDrive.TankDrive(leftin,rightin); //Pass to Tank Drive Function
// ------------------------------------------------------------------------------------------

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

//------------------------ vision -----------------------------

	std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
	float targetOffsetAngle_Horizontal = table->GetNumber("tx",0);
	float targetOffsetAngle_Vertical = table->GetNumber("ty",0);
	float targetArea = table->GetNumber("ta",0);
	float targetSkew = table->GetNumber("ts",0);

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

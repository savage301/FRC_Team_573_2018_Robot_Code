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


	frc::Joystick controller1{ Driver1 };  // Xbox controller 1
	frc::Joystick controller2{ Driver2 };  // Xbox controller 2
	Drive MyDrive; 			//Calling Drive.h
	Appendage MyAppendage; 	//Calling Appendage.h
	Log myLog; 				//Calling Log.h
	Autonomous myAuto; //Calling Autonomus.h
	int count;
	double plustime;
	bool reset1;
	double timesec;

	frc::PowerDistributionPanel board;

	void RobotInit() override {
		//m_chooser.AddDefault("Default Auto", &m_defaultAuto);
		//m_chooser.AddObject("My Auto", &m_myAuto);
		//frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

		//Turning off Limelight LEDs upon robot init
		std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
		table->PutNumber("ledMode", 1);

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
		//rampcontrol = 0;
		climbcontrol = false;
		//Turning off Limelight LEDs upon robot init
		std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
		table->PutNumber("ledMode", 0);
		MyAppendage.Climber(false);

	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();

		//Turning off Limelight LEDs when robot is disabled
		std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
		table->PutNumber("ledMode", 1);
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
		/*std::string autoSelected = frc::SmartDashboard::GetString(
				"Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			m_autonomousCommand = &m_myAuto;
		} else {
			m_autonomousCommand = &m_defaultAuto;
		}

		m_autonomousCommand = m_chooser.GetSelected();

		if (m_autonomousCommand != nullptr) {
			m_autonomousCommand->Start();
		}*/

		//myAuto.ModeSelect();
		MyAppendage.ClawWrist(false,true);
		std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
		table->PutNumber("ledMode",0);
		double delaysec = frc::SmartDashboard::GetNumber("Delay",0);
		//frc::SmartDashboard::PutString("DB/String 4",std::to_string(delaysec));

		count = delaysec*(-1000/20);

		//count = 0;
		reset1 = true;
		MyDrive.GyroReset();
		MyDrive.EncoderReset();


	}

	void AutonomousPeriodic() override {
		std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
		table->PutNumber("ledMode",1);
		frc::Scheduler::GetInstance()->Run();
		timesec = count * 20.0/1000;

		string layout = DriverStation::GetInstance().GetGameSpecificMessage();

		char switchclose = layout[0];
		char scale = layout[1];
		char switchfar = layout[2];
		int leftorright = 0;
		int leftorrightscale = 0;

// ----- Setting Auto Selection Variables --------
		if (switchclose == 'R'){
			leftorright = 1;
		}else{
			leftorright = -1;
		}
		if (scale == 'R'){
					leftorrightscale = 1;
				}else{
					leftorrightscale = -1;
				}

			// -1 left; 0:Middle; 1 Right
		string startleftorrightstring = frc::SmartDashboard::GetString("Start Location","0");
		int startleftorright = 0;
		if (startleftorrightstring == "0"){
			startleftorright = 0;
		}
		else if (startleftorrightstring == "1"){
			startleftorright = 1;
		}
		else if (startleftorrightstring == "-1"){
			startleftorright = -1;
		}

		string autoselectorstring = frc::SmartDashboard::GetString("Auto Selector","0");

		int autoselector = 0;
			if (autoselectorstring == "0"){
				autoselector = 0;
			}
			else if (autoselectorstring == "1"){
				autoselector = 1;
			}
			else if (autoselectorstring == "2"){
				autoselector = 2;
			}
			else if (autoselectorstring == "3"){
				autoselector = 3;
			}
			else if (autoselectorstring == "4"){  //Scale no matter what
				autoselector = 4;
			}


		frc::SmartDashboard::PutString("DB/String 7",std::to_string(autoselector));
		frc::SmartDashboard::PutString("DB/String 8",std::to_string(timesec));


//Junk Code ------------------------------------------
		/*if (timesec<2){
		MyDrive.GyroSetpoint(90);
			//MyDrive.TankDrive(1,1);
		}
		else if(timesec<4){
			MyDrive.GyroSetpoint(0);
		}
		else{
			MyDrive.TankDrive(0,0);
		}*/

		//

		//MyDrive.EncoderSetpoint(feet);
		//MyDrive.EncoderReset();
		//MyDrive.GyroSetpoint(degrees);
		//MyDrive.GyroReset();
//----------------------------------------------------------------

//Programming Tab Info
		myLog.ProgrammingTabInfoLog();
		MyDrive.ProgrammingTabInfoDrive();
		MyAppendage.ProgrammingTabInfoAppendage();


if (startleftorright == 0 && autoselector == 2){
//--------Switch from center Automode (Assuming Right side pad) ---------------------
		if (timesec<0)
		{
			MyDrive.TankDrive(0,0);
		}
		else if (timesec<.25){
			MyAppendage.Elevator(0, false,true,false,false);
		}
		else if (timesec<.5){
			MyAppendage.Elevator(0, true,false,false,false);
			MyAppendage.Claw(1);
		}
		else if (timesec<1.25){
			MyDrive.EncoderSetpoint(2);
			MyAppendage.Claw(0);
			MyAppendage.Elevator(0, false,false,false,false);
			reset1 = true;
		}
		else if (timesec<1.7){
			if(reset1){
							MyDrive.EncoderReset();
							MyDrive.GyroReset();
							reset1 = false;
						}
			MyDrive.GyroSetpoint(90*leftorright);
			MyAppendage.Claw(1);
		}
		else if (timesec<1.8){
			reset1=true;
		}
		else if (timesec<3.5){

			if(reset1){
				MyDrive.EncoderReset();
				MyDrive.GyroReset();
				reset1 = false;
			}
			MyAppendage.Claw(0);
			if (leftorright == -1){
				MyDrive.EncoderSetpoint(6.5);
			}
			else{
				MyDrive.EncoderSetpoint(3.5);
			}

		}
		else if (timesec<3.6){
			reset1 = true;
		}
		else if (timesec<4.2){
			if(reset1){
							MyDrive.EncoderReset();
							MyDrive.GyroReset();
							reset1 = false;
			}
			MyDrive.GyroSetpoint(-80*leftorright);
			MyAppendage.Claw(1);
		}
		else if (timesec<4.5){


				MyDrive.EncoderReset();
				MyDrive.GyroReset();
				reset1 = true;

			//MyAppendage.Elevator(0, false,true,false,false);
			MyDrive.TankDrive(0,0);
			MyAppendage.Claw(0);

		}
		else if (timesec<6){
			if(reset1){
										MyDrive.EncoderReset();
										MyDrive.GyroReset();
										reset1 = false;
						}
			MyDrive.EncoderSetpoint(7.5);
			MyAppendage.Elevator(0, false,true,false,false);
		}
		else if (timesec<7){
			MyAppendage.Claw(-1);
			MyDrive.TankDrive(0,0);
			MyAppendage.Elevator(0, false,false,false,false);
		}
		//Added Stuff
		else if (timesec<8){
			MyAppendage.Claw(0);
			MyDrive.EncoderSetpoint(2);
			MyAppendage.Elevator(0, false,false,false,false);
				}
		else if (timesec<9){
					MyAppendage.Claw(0);
					MyDrive.TankDrive(0,0);
					MyAppendage.Elevator(0, true,false,false,false);
						}

		// End Added Stuff
		else{
			MyDrive.TankDrive(0,0);
			MyAppendage.Claw(0);
			MyAppendage.Elevator(0, false,false,false,false);
		}
// ---------------------------------------------------------------
}


else if ((abs(startleftorright) == 1 && autoselector == 2 && leftorright == startleftorright) or (abs(startleftorright) == 1 && autoselector == 3 && leftorrightscale != startleftorright && leftorright == startleftorright)){
// -------------- Side Start Switch (Assuming Right side pad)------------------------------
		if (timesec<0)
		{
			MyDrive.TankDrive(0,0);
		}
		else if (timesec<.25){
			MyAppendage.Elevator(0, false,true,false,false);
		}
		else if (timesec<.5){
					MyAppendage.Elevator(0, true,false,false,false);
					MyAppendage.Claw(1);
				}
		else if (timesec<3.5){
			MyDrive.EncoderSetpoint(12);
			MyAppendage.Elevator(0, false,false,false,false);
			MyAppendage.Claw(0);
			reset1 = true;
		}
		else if (timesec<4){
					if(reset1){
						MyDrive.EncoderReset();
						MyDrive.GyroReset();
						reset1 = false;
						}
					MyDrive.GyroSetpoint(-90*startleftorright);
					MyAppendage.Claw(1);

				}
		else if (timesec<4.5){

				MyAppendage.Elevator(0, false,true,false,false);
				MyDrive.TankDrive(0,0);
				reset1=true;
				MyAppendage.Claw(0);

		}

		else if (timesec<6){
			if(reset1){
			MyDrive.EncoderReset();
			MyDrive.GyroReset();
			reset1 = false;
			}

			MyDrive.EncoderSetpoint(3);
			MyAppendage.Elevator(0, false,false,false,false);

		}
		else if (timesec<7.5){
			MyAppendage.Claw(-.8);
			MyDrive.TankDrive(0,0);
		}
		else{
			MyDrive.TankDrive(0,0);
			MyAppendage.Claw(0);
		}

// ---------------------------------------------------------------------------------------
}


else if (abs(startleftorright) == 1 && autoselector == 3 && leftorrightscale == startleftorright){
	//Scale Auto if they line up
						if (timesec<0){
							MyDrive.TankDrive(0,0);
						}
						else if (timesec<.5){
							MyAppendage.Elevator(0, false,true,false,false);
						}
						else if (timesec<5.3){
							MyDrive.EncoderSetpointNonZeroGyro(22,0);	// Drive Past Switch
							MyAppendage.Elevator(0, false,false,false,false);
							reset1=true;
						}
							else if ( timesec < (7.75)){
								if(reset1){
									MyDrive.EncoderReset();
									reset1 = false;
								}
								MyAppendage.Elevator(0, false,false,false,true);
								MyDrive.TankDrive(0,0);
							}
							else if ( timesec < (9.5)){
								MyDrive.GyroSetpoint(-80*startleftorright); // Turn Left
								MyAppendage.Elevator(0, false,false,false,false);
							}
							else if ( timesec < (9.9)){
								MyAppendage.Claw(-.8); // Spit box out
								MyDrive.TankDrive(0,0);
							}
							else if (timesec < (11.3)){
								MyAppendage.Claw(0); //
								MyDrive.GyroSetpoint(0); // Turn Out
							}
							else if (timesec < (12)){
								MyAppendage.Elevator(0,false,false,false,false);
								MyDrive.TankDrive(0,0);
							}
							else if (timesec < (12.5)){
								MyAppendage.Elevator(0,false,false,false,false);
							}
							else{
								MyDrive.TankDrive(0,0);
								MyAppendage.Elevator(0,false,false,false,false);
								MyAppendage.Claw(0);
							}

/*
	// -------------- Side Start Scale (Assuming Right side pad)------------------------------
		bool switchval;
		if (leftorright == startleftorright){
			switchval = true; //true is not on our side false is on our side
		}
		else{
			switchval = false;
		}

		if (timesec<0){
			MyDrive.TankDrive(0,0);
		}
		else if (timesec<.5){
			MyAppendage.Elevator(0, false,true,false,false);
		}
		else if (timesec<4.5){
			MyDrive.EncoderSetpoint(21.5);
			MyAppendage.Elevator(0, false,false,false,false);
			reset1=true;
		}
		else if (timesec<6){
			if(reset1){
				MyDrive.EncoderReset();
				MyDrive.GyroReset();
				reset1 = false;
			}
			MyAppendage.Elevator(0, false,false,false,true);
			MyDrive.TankDrive(0,0);
		}

		else if(timesec<6.5){
			MyDrive.GyroSetpoint(-35*startleftorright);
			reset1 = true;

		}
		else if (timesec<7.5){
			if(reset1){
				MyDrive.EncoderReset();
				MyDrive.GyroReset();
				reset1 = false;
						}
			MyDrive.EncoderSetpoint(1);
			MyAppendage.Elevator(0, false,false,false,false);
		}
		else if (timesec<8){
			MyAppendage.Claw(-.8);
			MyDrive.TankDrive(0,0);
			reset1 = true;
		}
		else if (timesec<9){
			if(reset1){
				MyDrive.EncoderReset();
				MyDrive.GyroReset();
				reset1 = false;
			}
			MyDrive.EncoderSetpoint(-1);
			MyAppendage.Claw(0);
		}
		else if (timesec<10){
			reset1 = true;
			MyDrive.TankDrive(0,0);
			MyAppendage.Elevator(0, true,false,false,false);
		}
		else if (timesec<13.5){
			if(reset1){
				MyDrive.EncoderReset();
				MyDrive.GyroReset();
				reset1 = false;
									}
			MyDrive.GyroSetpoint(-100*startleftorright);
		}
		else if (timesec<14.5){
			bool boxinclaw = MyAppendage.LightGateGet();
			if (boxinclaw){
				MyDrive.TankDrive(0,0);
			}
			else{
			MyDrive.CameraCenter(-.75);
			MyAppendage.Claw(.8);
			}
		}
		else if (timesec<17){
		if(switchval){
						count = 100000; //Messes with count to not place the cube on switch if its not infront of the right one.
								}
		}
		else if (timesec<18.5){

			if(reset1){
				MyDrive.EncoderReset();
				MyDrive.GyroReset();
				reset1 = false;
			}
			MyDrive.EncoderSetpoint(-1);
		}

		//Skip rest if switch isn't ours
		else if (timesec<21.5){
			if(switchval){
				count = 100000; //Messes with count to not place the cube on switch if its not infront of the right one.
			}
			MyAppendage.Elevator(0, false,true,false,false);
			MyDrive.TankDrive(0,0);
			reset1=true;
		}
		else if (timesec<22.5){
			if(reset1){
				MyDrive.EncoderReset();
				MyDrive.GyroReset();
				reset1 = false;
						}
			MyDrive.EncoderSetpoint(1);
			MyAppendage.Elevator(0, false,false,false,false);
		}
		else if (timesec<23.5){
			MyAppendage.Claw(-.8);
			MyDrive.TankDrive(0,0);
		}
		else{
			MyAppendage.Elevator(0, false,false,false,false);
			MyDrive.TankDrive(0,0);
			MyAppendage.Claw(0);
		}
*/

// ---------------------------------------------------------------------------------------
}
else if ( autoselector == 0){
	// Do nothing
	MyDrive.TankDrive(0,0);
}

// ------------------------- Scale Only ------------------
else if (autoselector == 4){
// -------------- Side Start Scale (Assuming Right side pad)------------------------------
		bool scalesideval;
		if (leftorrightscale == startleftorright){
			scalesideval = false;
		}
		else{
			scalesideval = true; //Need To Cross the field
		}

// -- Same Side Auto

		if(not scalesideval){
			if (timesec<0){
										MyDrive.TankDrive(0,0);
									}
									else if (timesec<.5){
										MyAppendage.Elevator(0, false,true,false,false);
									}
									else if (timesec<5.3){
										MyDrive.EncoderSetpointNonZeroGyro(22,0);	// Drive Past Switch
										MyAppendage.Elevator(0, false,false,false,false);
										reset1=true;
									}
										else if ( timesec < (7.75)){
											if(reset1){
												MyDrive.EncoderReset();
												reset1 = false;
											}
											MyAppendage.Elevator(0, false,false,false,true);
											MyDrive.TankDrive(0,0);
										}
										else if ( timesec < (9.5)){
											MyDrive.GyroSetpoint(-80*startleftorright); // Turn Left
											MyAppendage.Elevator(0, false,false,false,false);
										}
										else if ( timesec < (9.9)){
											MyAppendage.Claw(-.8); // Spit box out
											MyDrive.TankDrive(0,0);
										}
										else if (timesec < (11.3)){
											MyAppendage.Claw(0); //
											MyDrive.GyroSetpoint(0); // Turn Out
										}
										else if (timesec < (12)){
											MyAppendage.Elevator(0,false,false,false,false);
											MyDrive.TankDrive(0,0);
										}
										else if (timesec < (12.5)){
											MyAppendage.Elevator(0,false,false,false,false);
										}
										else{
											MyDrive.TankDrive(0,0);
											MyAppendage.Elevator(0,false,false,false,false);
											MyAppendage.Claw(0);
										}

		}

// Cross Field Auto
		if(scalesideval){
			plustime = 8.5-4; //extra time to be added to other commands for field traverse
			if (timesec<0){
						MyDrive.TankDrive(0,0);
					}
					else if (timesec<.5){
						MyAppendage.Elevator(0, false,true,false,false);
					}
					else if (timesec<4){
						MyDrive.EncoderSetpointNonZeroGyro(16.5,0);	// Drive Past Switch
						MyAppendage.Elevator(0, false,false,false,false);
						reset1=true;
					}

			//Traverse Field
					else if (timesec < 4.5){

								MyDrive.GyroSetpoint(-90*startleftorright); // Turn Left
							}
					else if (timesec < 8){
								if(reset1){
									MyDrive.EncoderReset();
									reset1 = false;
								}
								MyDrive.EncoderSetpointNonZeroGyro(20,-90*startleftorright); //Drive across field
							}
					else if (timesec < 8.5){
								MyDrive.GyroSetpoint(0);
								reset1 = true;
							}

			//Back To Normal
					else if( timesec < (5.3+plustime)){
							if(reset1){
								MyDrive.EncoderReset();
								reset1 = false;
							}
							MyDrive.EncoderSetpointNonZeroGyro(5.5,0);
						}
						else if ( timesec < (7+plustime)){
							MyAppendage.Elevator(0, false,false,false,true);
							MyDrive.TankDrive(0,0);
						}
						else if ( timesec < (8+plustime)){
							MyDrive.GyroSetpoint(-80*startleftorright); // Turn Left
							MyAppendage.Elevator(0, false,false,false,false);
						}
						else if ( timesec < (8.3+plustime)){
							MyAppendage.Claw(-.8); // Spit box out
							MyDrive.TankDrive(0,0);
						}
						else if (timesec < (9.3+plustime)){
							MyAppendage.Claw(0); //
							MyDrive.GyroSetpoint(0); // Turn Out
						}
						else if (timesec < (10+plustime)){
							MyAppendage.Elevator(0,true,false,false,false);
							MyDrive.TankDrive(0,0);
						}
						else if (timesec < (10.5+plustime)){
							MyAppendage.Elevator(0,false,false,false,false);
						}
		}

//

/*
		if (timesec<0){
			MyDrive.TankDrive(0,0);
		}
		else if (timesec<.5){
			MyAppendage.Elevator(0, false,true,false,false);
		}
		else if (timesec<4){
			MyDrive.EncoderSetpointNonZeroGyro(15,0);	// Drive Past Switch
			MyAppendage.Elevator(0, false,false,false,false);
			reset1=true;
		}

		else if (timesec < 15){
			//Turn Or drive forward
			if (scalesideval){

				// Traverse field commands
				if (timesec < 4.5){

					MyDrive.GyroSetpoint(-90*startleftorright); // Turn Left
				}
				else if (timesec < 8){
					if(reset1){
						MyDrive.EncoderReset();
						reset1 = false;
					}
					MyDrive.EncoderSetpointNonZeroGyro(20,-90*startleftorright);
				}
				else if (timesec < 8.5){
					MyDrive.GyroSetpoint(0);
					reset1 = true;
				}

				plustime = 8.5-4; //extra time to be added to other commands for field traverse
			}


			else{
				plustime = 0;
			}

			if( timesec < (plustime+5.3)){
				if(reset1){
					MyDrive.EncoderReset();
					reset1 = false;
				}
				MyDrive.EncoderSetpointNonZeroGyro(7,0);
			}
			else if ( timesec < (plustime+7)){
				MyAppendage.Elevator(0, false,false,false,true);
				MyDrive.TankDrive(0,0);
			}
			else if ( timesec < (plustime+8)){
				MyDrive.GyroSetpoint(-80*startleftorright); // Turn Left
				MyAppendage.Elevator(0, false,false,false,false);
			}
			else if ( timesec < (plustime+8.3)){
				MyAppendage.Claw(-.8); // Spit box out
				MyDrive.TankDrive(0,0);

			}
			else if (timesec < (plustime+9.3)){
				MyAppendage.Claw(0); //
				MyDrive.GyroSetpoint(0); // Turn Out
			}
			else if (timesec < (plustime+10)){
				MyAppendage.Elevator(0,true,false,false,false);
				MyDrive.TankDrive(0,0);
			}
			else if (timesec < (plustime+10.5)){
				MyAppendage.Elevator(0,false,false,false,false);
			}

		}
*/
}
// ---------------------------------------------------------------------------------------



// ------ End Scale Only -------------------------
//Default Auto Cross Line
else{
	if(timesec<0){
	MyDrive.TankDrive(0,0);
	}
	else if (timesec<.25){
		MyAppendage.Elevator(0, false,true,false,false);
	}
	else if (timesec<.5){
	MyAppendage.Elevator(0, true,false,false,false);
	MyAppendage.Claw(1);
	}
	else if(timesec<2.5){
	//Drive forward
	MyDrive.EncoderSetpoint(8);
	MyAppendage.Claw(0);
	MyAppendage.Elevator(0, false,false,false,false);
	}
	else{
	MyDrive.TankDrive(0,0);
	}
}

count = count + 1;
} //End Auto Peroidic

	void TeleopInit() override {
		std::shared_ptr<NetworkTable> table =  NetworkTable::GetTable("limelight");
		table->PutNumber("ledMode",0);
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (m_autonomousCommand != nullptr) {
			m_autonomousCommand->Cancel();
			m_autonomousCommand = nullptr;
		}

		myLog.Create(); //Start New Log File


	}

	void TeleopPeriodic() override {

		frc::Scheduler::GetInstance()->Run();
		MyAppendage.GetDistanceUltrasonic();

// -------------------- Logging Code ---------------------------------------------/
		//myLog.Write("Test Output");
		//myLog.PDP(15, 5, false);


// ---------------------------------------------------------------------------



// -------------------- Logging Code ---------------------------------------------/
		//Place code to write current setitings to log file
		//myLog.Write("Test Output");
		//myLog.PDP(15, 5, false);

// ---------------------------------------------------------------------------

// --------------- Driving --------------------------------------

		double leftin = pow(controller1.GetRawAxis(1), 3); //Get Drive Left Joystick Y Axis Value
		double rightin = pow(controller1.GetRawAxis(5), 3); //Get Drive right Joystick Y Axis Value
		bool AButton = controller1.GetRawButton(1);
		bool BButton = controller1.GetRawButton(2);
		bool XButton = controller1.GetRawButton(3);
		bool YButton = controller1.GetRawButton(4);
		bool LBButton = controller1.GetRawButton(5);
		double RTrigger = controller1.GetRawAxis(3);


		bool RTriggerButton;
		if (abs (RTrigger) > .5){
			RTriggerButton = true;
		}
		else {
			RTriggerButton = false;
		}

		if(AButton) {
		// ------------Camera Aided Driving ----------------------
			MyDrive.CameraCenter(leftin);
			MyDrive.Booster(false); //false is low-gear

		} else if(BButton) {

			if (gyroreset){ //resets gyro if first time through loop
				MyDrive.GyroReset();
				gyroreset = false;
			}

			MyDrive.StraightGyro(leftin); //Use Gryo to drive straight
			//MyDrive.GyroSetpoint(90); // Gryo setpoint test TO BE REMOVED

		} else if(YButton) {

			MyDrive.EncoderSetpoint(4); // Encoder setpoint test TO BE REMOVED

		} else {

			gyroreset = true;
			MyDrive.TankDrive(leftin,rightin); //Pass to Tank Drive Function
			MyDrive.Booster(RTriggerButton);

		}


		if(XButton)
			MyDrive.GyroReset(); //Gyro reset TO BE REMOVED

		if(LBButton)
			MyDrive.EncoderReset(); //Encoder rest TO BE REMOVED


// ------------- Dashboard Indicator Code ---------------------------------
	//Total Current : Flags if total current exceed 400 amps for more than 1 sec to dashboard
		myLog.PDPTotal();

	//Box in Vision : Checks to see if box is aquired by vision system
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

// TEMP LED CODE

		bool btn1 = controller1.GetRawButton(7);
		bool btn2 = controller1.GetRawButton(8);

		if (cubeBool or btn2){
			btn2 = true;
		}

		MyAppendage.LEDs(btn1,btn2);
// ---------------

	//Box in Claw : Checks if light gate is open or closed
		MyAppendage.LightGateGet();

	//Current Mismatch : Checks to see if drive motor have a large current mismatch and prints to dashboard
		myLog.DrivetrainCurrentCompare(0,leftin);
		myLog.DrivetrainCurrentCompare(1,leftin);
		//myLog.DrivetrainCurrentCompare(2,leftin);
		myLog.DrivetrainCurrentCompare(13,rightin);
		myLog.DrivetrainCurrentCompare(14,rightin);
		//myLog.DrivetrainCurrentCompare(15,rightin);

	//Over Plates Check
		MyAppendage.GetDistanceUltrasonic(); // Check to see if over plates:Set indicator on dashboard


	//Programming Tab Info
		myLog.ProgrammingTabInfoLog();
		MyDrive.ProgrammingTabInfoDrive();
		MyAppendage.ProgrammingTabInfoAppendage();

// ----------------------------Claw Control----------------------------
		double clawinraw = controller2.GetRawAxis(2); //Claw in
		double clawoutraw = controller2.GetRawAxis(3); //Claw out
		bool clawinbtn;
		bool clawoutbtn;

		//Taking the claw in or out raw value and making it a boolean
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

		//Setting claw talons power settings
		if (clawinbtn){  //&& rampcontrol != 1){
			MyAppendage.Claw(1); //Claw in
		}
		else if (clawoutbtn){// && rampcontrol != 1){
			MyAppendage.Claw(-1); // Claw out
		}
		else {
			MyAppendage.Claw(0); //Claw stop
		}

// Random Logging code???
		//myLog.PDP(1, 5, true);


//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------

//---------------------------Elevator Code--------------------------------------------
		double elevatorraw = controller2.GetRawAxis(1);
		bool elevatorground = controller2.GetRawButton(1);
		bool elevatorpos1 = controller2.GetRawButton(2);
		bool elevatorpos2 = controller2.GetRawButton(3);
		bool elevatorpos3 = controller2.GetRawButton(4);
		bool encoderreset = controller2.GetRawButton (7);

		//Call elevator function
		MyAppendage.Elevator(elevatorraw, elevatorground, elevatorpos1, elevatorpos2, elevatorpos3);

		//Encoder Reset TO BE REMOVED
		if (encoderreset){
		MyAppendage.EncoderReset();
		}

//------------------------------------------------------------------------------------



//----------------------- Claw Wrist -----------------------------------------
		//REally is climber clyinder
	bool ClawWristButtonUp = controller2.GetRawButton(5);
	bool ClawWristButtonDown;

	if (not ClawWristButtonUp){
		ClawWristButtonDown = true;
	}
	MyAppendage.ClawWrist(ClawWristButtonUp,ClawWristButtonDown);
//--------------------------------------------------------------------

//---------------------- Climber ---------------------------
	bool climbbutton1 = controller1.GetRawButton(5);
	bool climbbutton2 = controller1.GetRawButton(6);
	double climbPOV = controller1.GetPOV(0);
	bool climbbutton3;

	if (climbPOV < 120 && climbPOV > 60){
		climbbutton3 = true;
	}
	else{
		climbbutton3 = false;
	}

	if (climbbutton1 && climbbutton2){
		climbcontrol = true;
	}
	if (climbbutton3){
		climbcontrol = false;
	}
	MyAppendage.Climber(climbcontrol);
}

//----------------------------------------------------------



/*
//---------------------------Ramps-----------------------------
	//Ramps down with Lbumper and Rbumper ramps back up with right joystick press
	bool rampbutton1 = controller2.GetRawButton(5);
	bool rampbutton2 = controller2.GetRawButton(6);
	bool rampbutton3 = controller2.GetRawButton(10);
	bool rampup1 = controller2.GetRawButton (7); //Ramp up 1
	bool rampup2 = controller2.GetRawButton (8); //Ramp up 2

	if (rampbutton1 && rampbutton2){
		rampcontrol = 1;
	}
	if (rampbutton3){
		rampcontrol = 0;
	}

	MyAppendage.Ramp(rampcontrol,clawinbtn,clawoutbtn,rampup1,rampup2);


	}
*/


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
	//bool rampcontrol = 0;
	bool climbcontrol = false;
	bool gyroreset = true;
};

START_ROBOT_CLASS(Robot)

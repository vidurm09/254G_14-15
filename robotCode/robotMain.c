#pragma config(Sensor, in1,    autoPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    posPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rDriveEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rLiftEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  lDriveEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  lLiftEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  liftDetectLeft, sensorTouch)
#pragma config(Sensor, dgtl10, liftDetectRight, sensorTouch)
#pragma config(Motor,  port1,           driveLB,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           driveLF,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           liftLB,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftLT,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           intakeR,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           intakeL,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftRT,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftRB,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           driveRF,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          driveRB,       tmotorVex393_HBridge, openLoop, reversed)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#pragma systemFile

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "robotGeneral.c"
#include "robotDrive.c"
#include "robotArm.c"
#include "robotAuto.c"

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................

	  UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
	}
}

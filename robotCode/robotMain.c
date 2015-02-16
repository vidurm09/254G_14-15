#pragma config(Sensor, in1,    autoPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    posPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rDriveEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rLiftEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  lDriveEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  lLiftEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  dumpSolenoid,   sensorDigitalOut)
#pragma config(Sensor, dgtl11, liftDetectLeft, sensorTouch)
#pragma config(Sensor, dgtl12, liftDetectRight, sensorTouch)
#pragma config(Motor,  port1,           driveLB,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           intakeR,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           intakeL,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           driveLF,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           driveRF,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftLT,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftLB,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           liftRB,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           liftRT,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          driveRB,       tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#pragma systemFile

#include "Vex_Competition_Includes.c"
#include "robotDrive.c"
#include "robotArm.c"
#include "robotAuto.c"
#include "robotGeneral.c"

void pre_auton()
{
  bStopTasksBetweenModes = true;
}
//Autonomous task
task autonomous()
{
  auto();
}
//User control task
task usercontrol()
{
	resetEncoder();
	startTask(armPID);
	toArmStream = true;
	while (true)
	{
	  drive();
	}
}

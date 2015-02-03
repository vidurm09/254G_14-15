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

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#pragma systemFile

#include "Vex_Competition_Includes.c"
#include "robotGeneral.c"
#include "robotDrive.c"
#include "robotArm.c"
#include "robotAuto.c"

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
	while (true)
	{
	  drive();
	}
}

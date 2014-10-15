#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    rightPot,       sensorPotentiometer)
#pragma config(Sensor, in2,    leftPot,        sensorPotentiometer)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           LB,            tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port2,           LF,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RB,            tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port4,           RF,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           ALB,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           ALT,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           ART,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           ARB,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           IL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          IR,            tmotorVex393_HBridge, openLoop)

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

float targetValue;
float leftDriveTargetValue;
float rightDriveTargetValue;
int rightArmTarget;
int leftArmTarget;
bool isRun = true;

double mapRange(double a1,double a2,double b1,double b2,double s)//a1,a2 -> input range; b1,b2 -> output range; s->increment
{
    return b1 + (s-a1)*(b2-b1)/(a2-a1);
}

task driveBasePID()
{
	//Left motor control vars
	float left_Kp = 1.5;
	float left_Ki = 0.000;
	float left_Kd = 0;
	float left_error = 0;
	float left_integral = 0;
	float left_derivative = 0;
	float left_previousError = 0;
	float left_speed = 0;
	float left_sensorReading = 0;
	float left_zero = 0;
	//Right motor control vars
	float right_Kp = 1.5;
	float right_Ki = 0.000;
	float right_Kd = 0;
	float right_error =0;
	float right_integral = 0;
	float right_derivative = 0;
	float right_previousError = 0;
	float right_speed = 0;
	float right_sensorReading = 0;
	float right_zero = 0;


	while (isRun) 
	{
		//Left side PID
		left_sensorReading = nMotorEncoder[LB];
		left_error = leftDriveTargetValue - left_sensorReading;
		left_integral = left_integral + left_error;
		if (left_error == 0)
	  {
	  	left_integral = 0;
	  }

	 if (abs(left_error) > 50000)
	 {
	   left_integral = 50000;
	 }
	 left_derivative = left_error - left_previousError;
	 left_previousError = left_error;
	 left_speed = left_Kp*left_error + left_Ki*left_integral + left_Kd*left_derivative;


	 //Right side PID
	 right_sensorReading = -nMotorEncoder[RB];
		right_error = rightDriveTargetValue - right_sensorReading;
		right_integral = right_integral + right_error;
		if (right_error == 0)
	  {
	  	right_integral = 0;
	  }

	 if (abs(right_error) > 50000)
	 {
	   right_integral = 50000;
	 }

		 right_derivative = right_error - right_previousError;
		 right_previousError = right_error;
	 right_speed = right_Kp*right_error + right_Ki*right_integral + right_Kd*right_derivative;
	 
	 if (right_error < 6 && right_error > -6)
	 {
	   right_zero = right_zero + 1;
	 }
	 //writeDebugStreamLine("%f,%f",left_speed,targetValue);
	 //writeDebugStreamLine("%f,%f",right_speed,targetValue);
	 //left_speed = left_speed;
	 writeDebugStreamLine("%f,%f, %f, %f",right_speed,targetValue,right_sensorReading,left_zero);
	 writeDebugStreamLine("%f,%f, %f, %f",left_speed,targetValue,left_sensorReading,right_zero);
	 motor[LB]=motor[LF]=left_speed;
	 motor[RB]=-right_speed;
	 motor[RF]=right_speed;
	 wait1Msec(10);
	 if (left_error < 6 && left_error > -6)
	 {
	   left_zero = left_zero + 1;
	   
	 }
	 if (left_zero > 8 && right_zero >8 ){
	 		isRun = False;
	 }
	}
	//isRun= False;
}
void autonomousDrive(int leftSide, int rightSide)
{
	leftDriveTargetValue = leftSide;
	 rightDriveTargetValue = rightSide;
	startTask(driveBasePID);
}
void drivePID(float rightInches, float leftInches)
{
	int rightTarget = (rightInches)/((3.14*4)/392);
	int leftTarget = (leftInches)/((3.14*4)/392);
	writeDebugStreamLine("%f,%f",rightTarget,leftTarget);
	autonomousDrive(leftTarget, rightTarget);
}

task armPID()
{
	float left_arm_Kp = 1.5;
	float left_arm_error = 0;
	float left_arm_speed = 0;
	int left_armVal=0;

	float right_arm_Kp = 1.5;
	float right_arm_error = 0;
	float right_arm_speed = 0;
	int right_armVal=0;

	left_armVal = SensorValue[leftPot];
	if (left_armVal < 70)
	{
	left_arm_error = leftArmTarget-left_armVal;
	left_arm_speed = left_arm_Kp*left_arm_error;
	}
	else 
	{
		left_arm_speed = 0;
	}
	writeDebugStreamLine("%f,%f, %f, %f",left_arm_error,left_arm_speed,leftArmTarget,left_armVal);

	right_armVal = SensorValue[rightPot];
	right_arm_error = rightArmTarget-right_armVal;
	right_arm_speed = right_arm_Kp*right_arm_error;
	writeDebugStreamLine("%f,%f, %f, %f",right_arm_error,right_arm_speed,rightArmTarget,right_armVal);

	motor[ALB]=motor[ALT]=-left_arm_speed;
	motor[ARB]=motor[ART]=right_arm_speed;
}

void autonomousArm(int target)
{
	rightArmTarget = target;
	leftArmTarget = target;
	StartTask(armPID);
}


void pre_auton()
{
  bStopTasksBetweenModes = true;
	targetValue=4000;
  rightArmTarget = 0;
  leftArmTarget = 0;
}

task autonomous()
{
	//startTask(driveBase);

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

void drive()
{
	//int right_armVal;
	//int left_armVal;
	int armLoop = 0;
  motor[RF]=vexRT[Ch2];
  motor[RB]=-vexRT[Ch2];
  motor[LB]=motor[LF]=vexRT[Ch3];

  //Arm control
  if (vexRT[Btn6D]== 1)
	{
		motor[ALB]=motor[ALT]=127;
		motor[ARB]=motor[ART]=-127;
	}
	else if (vexRT[Btn6U] == 1)
	{
		motor[ALB]=motor[ALT]=-127;
		motor[ARB]=motor[ART]=127;
		armLoop = 0;
	}
	else
	{
		motor[ALB]=motor[ALT]=-0;
		motor[ARB]=motor[ART]=0;
		//rightArmTarget = SensorValue[leftPot];
		//leftArmTarget = SensorValue[rightPot];
		//startTask(armPID);
		}

	//Intake control
	if (vexRT[Btn5D]== 1)
	{
		motor[IR]=127;
		motor[IL]=127;
	}
	else if (vexRT[Btn5U] == 1)
	{
		motor[IR]=-127;
		motor[IL]=-127;
	}
	else
	{
		motor[IR]=0;
		motor[IL]=0;
	}
	/*right_armVal = SensorValue[leftPot];
	left_armVal = SensorValue[rightPot];
	armPID(right_armVal,left_armVal);*/
}


task usercontrol()
{
	while (true)
	{
		
		//drive();
		
	}
}

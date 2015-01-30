#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    rightPot,       sensorPotentiometer)
#pragma config(Sensor, in2,    leftPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    sideLeft,       sensorLineFollower)
#pragma config(Sensor, in5,    sideRight,      sensorLineFollower)
#pragma config(Sensor, in6,    centerLeft,     sensorLineFollower)
#pragma config(Sensor, in7,    centerMid,      sensorLineFollower)
#pragma config(Sensor, in8,    centerRight,    sensorLineFollower)
#pragma config(Sensor, dgtl1,  leftArmButtonTop, sensorDigitalIn)
#pragma config(Sensor, dgtl2,  leftArmButton,  sensorDigitalIn)
#pragma config(Sensor, dgtl3,  rightArmButton, sensorDigitalIn)
#pragma config(Sensor, dgtl4,  rightArmButtonTop, sensorDigitalIn)
#pragma config(Sensor, dgtl8,  solenoid,       sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           RF,            tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port2,           IR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           IL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LB,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LF,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           ARB,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           ART,           tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port8,           ALB,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           ALT,           tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port10,          RB,            tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"
#include "robotArmCode.c"
#include "robotDriveCode.c"

//Temp

float leftArmAngle;
float rightArmAngle;

float targetValue;
float leftDriveTargetValue=0;
float rightDriveTargetValue=0;
int rightArmTarget;
int leftArmTarget;
float left_currAngle;
float right_currAngle;
float currLeftDist;
float currRightDist;
float left_armAngle;
float right_armAngle;
float targetLeftDist;
float targetRightDist;
float left_armPow;
float right_armPow;
bool armMove;
bool armA;
bool driveA;
int armLoop = 0;
float right_inte;
float left_inte;
float armAngle;
bool softStop = false;
bool softStopTop = false;
int prevArmPosRight;
int prevArmPosLeft;

float mapRange(float a1,float a2,float b1,float b2,float s)//a1,a2 -> input range; b1,b2 -> output range; s->value input
{
    return b1 + (s-a1)*(b2-b1)/(a2-a1);
}

void moveArmAuton(float rAngle, float lAngle)
{
	left_armAngle = lAngle;
	right_armAngle = rAngle;
}
void setDrivePower(int left, int right)
{
	motor[RF]=right;
  motor[RB]=-right;
  motor[LB]=motor[LF]=left;
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

	bool isRun = true;

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

	 /*if (right_error < 6 && right_error > -6) //Comented out
	 {
	   right_zero = right_zero + 1;
	 }*/
	 motor[LB]=motor[LF]=left_speed;
	 motor[RB]=-right_speed;
	 motor[RF]=right_speed;
	 wait1Msec(10);
	 /*if (left_error < 6 && left_error > -6)
	 {
	   left_zero = left_zero + 1;

	 }
	 if (left_zero > 8 && right_zero >8 ){
	 		isRun = false;
	 }*/
	}
	//isRun= False;
}
void autonomousDrive(int leftSide, int rightSide)
{
	 leftDriveTargetValue = leftSide;
	 rightDriveTargetValue = rightSide;
}
void drivePID(float leftInches, float rightInches)
{
	int rightTarget = (rightInches)/((3.14*4)/392);
	int leftTarget = (leftInches)/((3.14*4)/392);
	writeDebugStreamLine("%f,%f,%f,%f",rightTarget,leftTarget,rightInches,leftInches);
	autonomousDrive(leftTarget, rightTarget);
}

float getRightArm()
{
	float value = (nMotorEncoder[ART])/2;
	return ((value/7.0)*360/392.0);
}
bool toArmStream = false;
float rAPrevError = 0;
float rAIntegral = 0;
float lAPrevError = 0;
float lAIntegral = 0;
float rAError;
float lAError;
float lADerivative;
float rADerivative;
float liftSetPt = 0;
float lastLiftSetPt = 0;

task armPID() {
	while(true) {
		rAError = liftSetPt - nMotorEncoder[ART];
		lAError = liftSetPt - nMotorEncoder[ALT];
		lAIntegral += lAError;
		rAIntegral += rAError;
		rADerivative = rAError - rAPrevError;
		//lDerivative = lAError - lAPrevError;
		//setLeftArm((armKp*lAError) + (armKi*lAIntegral) + (armKd*lADerivative));
		//setRightArm((armKp*RAError) + (armKi*RAIntegral) + (armKd*RADerivative));
	}
}

float getLeftArm()
{
	float value = (nMotorEncoder[ALT])/2;
	return ((value/7.0)*360/392.0);
}
void autonIntake(int power, int time)
{
	motor[IR]=power;
	motor[IL]=power;
}

void setRightArm(int power)
{
	motor[ARB] = power;
	motor[ART] = power;
}
void setLeftArm(int power)
{
	motor[ALB]= power;
	motor[ALT] = power;
}

task arm()
{
	float kP = 10;
	float kD = 0;
	float kI = 0;
	right_inte = 0;
	left_inte = 0;
	float left_lastError = 0;
	float right_lastError = 0;
	bool isArm = true;
	int isLeftArm = 0;
	int isRightArm = 0;
	int time = 0;

while(isArm)
{
	time++;
	right_currAngle = getRightArm();
	float right_error = right_armAngle-right_currAngle;
	float right_der = (right_error-right_lastError);
	right_inte = right_inte+right_error;
	right_armPow = right_error*kP;

	left_currAngle = getLeftArm();
	float left_error = left_armAngle-left_currAngle;
	float left_der = (left_error-left_lastError);
	left_inte = left_inte+left_error;
	left_armPow = left_error*kP;
	/*if(SensorValue[zero]&&armPow<0)
	{
		armPow = 0;
	}*/
	setLeftArm(left_armPow);
	setRightArm(right_armPow);
	writeDebugStreamLine("Left Power is %f,Left Error is %f\n,", left_armPow, left_error);
	writeDebugStreamLine("Right Power is %f,Left Error is %f\n,", right_armPow, right_error);
	left_lastError = left_error;
	if(abs(left_error)<=1&&abs(left_der)<=1)
	{
		armA=false;
		left_inte = 0;
	}

	right_lastError = right_error;
	if(abs(right_error)<=1&&abs(right_der)<=1)
	{
		armA=false;
		right_inte = 0;
	}
}
}


void pre_auton()
{
  bStopTasksBetweenModes = true;
	targetValue=4000;
  rightArmTarget = 0;
  leftArmTarget = 0;
  left_armAngle = 0;
  right_armAngle = 0;
}

int rampUp(float in){
    return ((int)ceil((in*in*in)/127.0))/127;
}

void arcadeRampUp()
{
	int channelThree = rampUp(vexRT[Ch3]);
	int channelOne = rampUp(vexRT[Ch1]);
	/*if(channelOne <= 5)
	{
		channelOne = 0;
	}
	if(channelThree <=5)
	{
		channelThree = 0;
	}*/
	motor[LB] = (channelThree + channelOne);
	motor[LF] = (channelThree + channelOne);
	motor[RF] = (channelThree - channelOne);
	motor[RB] = -(channelThree - channelOne);
}
void arcade()
{
	motor[LB] = (vexRT[Ch3] + vexRT[Ch1]);
	motor[LF] = (vexRT[Ch3] + vexRT[Ch1]);
	motor[RF] = (vexRT[Ch3] - vexRT[Ch1]);
	motor[RB] = -(vexRT[Ch3] - vexRT[Ch1]);
}
void tank()
{
	motor[RF]=vexRT[Ch2];
  motor[RB]=-vexRT[Ch2];
  motor[LB]=motor[LF]=vexRT[Ch3];
}

void armPresets()
{
	startTask(arm);
	if (vexRT[Btn8U]== 1)
	{
		moveArmAuton(80,80);
	}

	if (vexRT[Btn8D] == 1)
	{
		moveArmAuton(30,30);
	}
}

void driveArm()
{
	if (vexRT[Btn6D]== 1 && !softStop)
	{
		setLeftArm(-127);
		setRightArm(-127);
	}
else if (vexRT[Btn6U] == 1 && !softStopTop)
	{
		setRightArm(127);
		setLeftArm(127);
	}
	else
	{
		setRightArm(0);
		setLeftArm(0);
	}
}

void driveArmPID()
{
	if (vexRT[Btn6D]== 1 && !softStop)
	{
		stopTask(arm)
		setLeftArm(-127);
		setRightArm(-127);
		armLoop = 0;
	}
	else if (vexRT[Btn6U] == 1 && !softStopTop)
	{
		stopTask(arm);
		setRightArm(127);
		setLeftArm(127);
		armLoop = 0;
		prevArmPosLeft = getRightArm();
		prevArmPosRight = getLeftArm();
	}
	else
	{
		startTask(arm);
		if(armLoop == 0) {
			prevArmPosLeft = getRightArm();
			prevArmPosRight = getLeftArm();
		}
		armLoop++;
		moveArmAuton(prevArmPosLeft+1, prevArmPosRight);
	}
}

void resetEncoders()
{
	nMotorEncoder[LB] = 0;
	nMotorEncoder[RB] = 0;
	nMotorEncoder[ALT] = 0;
	nMotorEncoder[ART] = 0;
}

void drive()
{

	//int right_armVal;
	//int left_armVal;
  tank();
	//arcade();
  //Arm control
	driveArmPID();
	//driveArm();
	/*if (vexRT[Btn6D]== 1 && !softStop)
	{
		setLeftArm(-127);
		setRightArm(-127);
	}
else if (vexRT[Btn6U] == 1 && !softStopTop)
	{
		setRightArm(127);
		setLeftArm(127);
	}
	else
	{
		setRightArm(0);
		setLeftArm(0);
	}*/


	//armPresets();
	//Intake control

	if (vexRT[Btn7D] == 1)
	{
		SensorValue[solenoid] = 1;

	}
	if (vexRT[Btn7L] == 1)
	{
		SensorValue[solenoid] = 1;
		wait1Msec(2000);
		SensorValue[solenoid] = 0;

	}
	if (vexRT[Btn7U] == 1)
	{
		SensorValue[solenoid] = 0;
	}

	if (vexRT[Btn5U]== 1)
	{
		motor[IR]=-127;
		motor[IL]=-127;
	}
	else if (vexRT[Btn5D] == 1)
	{
		motor[IR]=127;
		motor[IL]=127;
	}
	else
	{
		motor[IR]=0;
		motor[IL]=0;
	}
	if (vexRT[Btn8U] == 1)
	{
	left_armAngle = 30;
	right_armAngle = 30;
	}
	else if (VexRT[Btn8D] ==1)
{
	left_armAngle = 0;
	right_armAngle = 0;

}
	if (sensorValue[leftArmButton] == 0 || sensorValue[rightArmButton]==0)
	{
		softStop = true;
	}
	else
	{
		softStop = false;
	}

	if (sensorValue[leftArmButtonTop] == 0 || sensorValue[rightArmButtonTop]==0)
	{
		softStopTop = true;
	}
	else
	{
		softStopTop = false;
	}
	/*right_armVal = SensorValue[leftPot];
	left_armVal = SensorValue[rightPot];
	armPID(right_armVal,left_armVal);*/
}

void dropCube()
{
	startTask(driveBasePID);
	startTask(arm);
	moveArmAuton(40,40);
	wait1Msec(500);
	moveArmAuton(5,5);
	//autonomousDrive(-300, -300);
	wait1Msec(500);
	/*motor[LB]=motor[LF]=-120;
	 motor[RB]=120;
	 motor[RF]=-120;*/
	 drivePID(-20,-20);
	 wait1Msec(500);
 //motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
	autonIntake(127,0);
	wait1Msec(3000);
	autonIntake(0,0);
	drivePID(-5, -5);
	wait1Msec(1000);
 	motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;

//	autonomousDrive(-300, -300);
	wait1Msec(1000);
	//autonomousDrive(-900,-900);

	/*
	drivePID(-10,-10);
	moveArmAuton(40,40);
	drivePID(10,0);*/
}

void dropSmallPoleRed()
{
	startTask(arm);
	startTask(driveBasePID);
	drivePID(-13,-30);
	moveArmAuton(55,55);
	wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(2000);
	autonIntake(0,0);
	stopTask(arm);
	stopTask(driveBasePID);

	//motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
	 //Vidur said he wont get mad if motors dont run later 11/3/14
}

void dropSmallPoleBlue()
{
	startTask(arm);
	startTask(driveBasePID);
	drivePID(-25,-15);
	wait1Msec(1000);
	//drivePID(-50,-50);
	moveArmAuton(50,50);
	wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(2000);
	autonIntake(0,0);
	drivePID(-40,-40);
	stopTask(arm);
	stopTask(driveBasePID);

	//motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
	 //Vidur said he wont get mad if motors dont run later 11/3/14
}
task stopAll()
{
	while(true)
{
	/*if (SensorValue[touchsensor] == 1)
	{
		stopTask(driveBasePID);
		motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
		stopTask(arm);
		motor[ALB]=motor[ALT]=motor[ARB]=motor[ALB]=0;
	}*/
}
}

void dropMediumPoleRedSky()
{
	startTask(arm);
	startTask(driveBasePID);
	moveArmAuton(20,20);
	wait1Msec(1000);
	moveArmAuton(0,0);
	//bool run = false;
	drivePID(14,17);
	autonIntake(127,127);
	wait1Msec(3000);
	moveArmAuton(80,80);
	wait1Msec(4000);
	drivePID(18,27);
wait1Msec(2000);

	autonIntake(-127,-127);
}

void dropMediumPoleRedNotSky()
{
	startTask(arm);
	startTask(driveBasePID);
	moveArmAuton(20,20);
	wait1Msec(1000);
	moveArmAuton(0,0);
	//bool run = false;
	drivePID(17,14);
	autonIntake(127,127);
	wait1Msec(3000);
	moveArmAuton(80,80);
	wait1Msec(4000);
	drivePID(32,16);
wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(3000);
	drivePID(10,10);

}

void dropMediumPoleBlueSky()
{
	startTask(arm);
	startTask(driveBasePID);
	moveArmAuton(20,20);
	wait1Msec(2000);
	moveArmAuton(0,0);
wait1Msec(500);
	//bool run = false;
	drivePID(17,14);
	autonIntake(127,127);
	wait1Msec(3000);
	moveArmAuton(80,80);
	wait1Msec(4000);
	drivePID(32,16);
wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(3000);
	autonIntake(127,127);
	drivePID(10,10);
}

void dropMediumPoleBlueNotSky()
{
	startTask(arm);
	startTask(driveBasePID);
	moveArmAuton(20,20);
	wait1Msec(1000);
	moveArmAuton(0,0);
	//bool run = false;
	drivePID(14,17);
	autonIntake(127,127);
	wait1Msec(3000);
	moveArmAuton(80,80);
	wait1Msec(4000);
	drivePID(18,27);
wait1Msec(2000);

	autonIntake(-127,-127);
}

void moveBackDrop()
{
	startTask(arm);
	startTask(driveBasePID);
	wait1Msec(1000);
	drivePID(-15,-15);
	wait1Msec(1000);
	moveArmAuton(30,30);
	wait1Msec(1000);
	motor[IL]= -127
	motor[IR] = -127
}

void lineSensorNonSky()//Run in a while loop
{
	int sonarVal;
	int numTurns = 0;
	//sonarVal = SensorValue(distSens);
	bool keepTurning = false;
	int threshold;
  threshold = 200; //Check Threshold with avg of light, avg of dark, and then the avg of those two
  //If the left sensor sees dark...
  if(SensorValue(centerLeft) < threshold)
  {
    //...counter-steer to the left.
    setDrivePower(100,127);
  }
  //If the center sensor sees dark...

  //If the right sensor sees dark...
  if(SensorValue(centerRight) < threshold)
  {
    //...counter steer to the right.
    setDrivePower(127,100);
  }
  if(SensorValue(centerMid) < threshold)
  {
    //...move forward.
    setDrivePower(127,127);
  }
	autonIntake(127,127);

	if (SensorValue(sideRight) < threshold)
	{
		setDrivePower(-127, 127);
		keepTurning = true;
		while (keepTurning)
		{
			if (SensorValue(sideRight) < threshold)
			{
				numTurns++;
				if (numTurns >= 2)
					{keepTurning=false;}
			}

	}

	/* if (SensorValue(sideLeft) < threshold)
	{
		setDrivePower(-127, 127);
		keepTurning = true;
		while (keepTurning)
		{
			if (SensorValue(sideRight) < threshold)
			{
				numTurns++;
				if (numTurns >= 2)
					{keepTurning=false;}
			}
		}
	}*/

}

}




task autonomous()
{
	resetEncoders();
	//startTask(driveBasePID);
	motor[RF]=+127;
  motor[RB]=-127;
  motor[LB]=motor[LF]=+127;
  wait1Msec(2000);
  motor[RF]=0;
  motor[RB]=0;
  motor[LB]=motor[LF]=0;
	// Remove this function call once you have "real" code.
}

task usercontrol()
{
 // Remove this function call once you have "real" code.
	//startTask(arm);
	//startTask(driveBasePID);
	//startTask(stopAll);
	//stopTask(arm);
 //	stopTask(driveBasePID);
 //	dropCube();
 //	startTask(stopAll);
	//stopTask(arm);
 //	stopTask(driveBasePID);
 //	stopTask(arm);4
	//startTask(stopAll);
	//dropSmallPoleBlue();
	while (true)
	{

	if (vexRT[Btn8D])
	{
		while(true)
		{
			lineSensorNonSky();
		}
	}
		drive();
		/*if(vexRT[Btn7D])
		{
			startTask(stopAll);
			startTask(arm);
			startTask(driveBasePID);
				//dropSmallPoleBlue();
			//moveBackDrop();
			//dropMediumPoleBlueSky();
			//ndropCube();
			wait1Msec(10000);
			stopTask(arm);
			stopTask(driveBasePID);
		}
			/*
				_   _     _   _   _   _   _
			 / \ / \   / \ / \ / \ / \ / \
			( H | I ) ( V | I | D | U | R )
			 \_/ \_/   \_/ \_/ \_/ \_/ \_/
		*/
		leftArmAngle = getLeftArm();
		rightArmAngle = getRightArm();
		writeDebugStreamLine("Left: %f, Right: %f",  getLeftArm(), getRightArm());
	}
}

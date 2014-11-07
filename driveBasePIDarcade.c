#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    rightPot,       sensorPotentiometer)
#pragma config(Sensor, in2,    leftPot,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  touchsensor,    sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           LB,            tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port2,           LF,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RB,            tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port4,           RF,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           ALB,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           ALT,           tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port7,           ART,           tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port8,           ARB,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           IL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          IR,            tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

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
float potTest;
float right_inte;
float left_inte;

float mapRange(float a1,float a2,float b1,float b2,float s)//a1,a2 -> input range; b1,b2 -> output range; s->value input
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
	 		isRun = false;
	 }
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
	motor[ALB]=-power;
	motor[ALT] = -power;
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
while(isArm)
{
	/*currAngle = getArm();
	float error = armAngle-currAngle;
	float der = (error-lastError);
	inte = inte+error;
	armPow = error*kP;*/

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
	/*lastError = error;
	if(abs(error)<=1&&abs(der)<=1)
	{
		armA=false;
		inte = 0;
	}*/
/*	if(abs(right_lastError-right_error)<2)
	{
		isRightArm = isRightArm + 1;
	}
	else
	{
		isRightArm = 0;
	}

	if(abs(left_lastError-left_error)<2)
	{
		isLeftArm = isLeftArm + 1;
	}
	else
	{
		isLeftArm = 0;
	}


	if((isLeftArm >= 5)&&(isRightArm >=5))
	{
		isArm = false;
	}
	*/
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
    return (int)ceil((in*in*in)/127.0);
}

void arcadeRampUp()
{
	int channelThree = rampUp(vexRT[Ch3]);
	int channelOne = rampUp(vexRT[Ch1]);
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

void drive()
{
	//int right_armVal;
	//int left_armVal;


	int armLoop = 0;
  //tank();
	arcade();

  //Arm control
  if (vexRT[Btn6D]== 1)
	{
		setLeftArm(-127);
		setRightArm(-127);
		//armAngle = getArm()+10;
	}
	else if (vexRT[Btn6U] == 1)
	{
		setRightArm(127);
		setLeftArm(127);
		//armAngle = getArm()-10;
		//armLoop = 0;
	}
	else
	{
		setRightArm(0);
		setLeftArm(0);

		//rightArmTarget = SensorValue[leftPot];
		//leftArmTarget = SensorValue[rightPot];
		//startTask(armPID);
		}

	//Intake control
	if (vexRT[Btn5U]== 1)
	{
		motor[IR]=127;
		motor[IL]=127;
	}
	else if (vexRT[Btn5D] == 1)
	{
		motor[IR]=-127;
		motor[IL]=-127;
	}
	else
	{
		motor[IR]=0;
		motor[IL]=0;
	}
	if (VexRT[Btn8U] == 1)
	{
	left_armAngle = 30;
	right_armAngle = 30;
	}
	else if (VexRT[Btn8D] ==1)
{
	left_armAngle = 0;
	right_armAngle = 0;

}
	/*right_armVal = SensorValue[leftPot];
	left_armVal = SensorValue[rightPot];
	armPID(right_armVal,left_armVal);*/
}

void moveArmAuton(float rAngle, float lAngle)
{
	left_armAngle = rAngle;
	right_armAngle = lAngle;
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
	motor[LB]=motor[LF]=-120;
	 motor[RB]=120;
	 motor[RF]=-120;
	 wait1Msec(500);
 motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
	autonIntake(-127,0);
	wait1Msec(2000);
	autonIntake(0,0);
	 motor[LB]=motor[LF]=-120;
	 motor[RB]=120;
	 motor[RF]=-120;
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
task autonomous()
{
	//startTask(driveBase);
	startTask(arm);
	startTask(driveBasePID);
	dropCube();  // Remove this function call once you have "real" code.
}
void dropSmallPoleRed()
{
	startTask(arm);
	startTask(driveBasePID);
	drivePID(-15,-25);
	moveArmAuton(50,50);
	wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(2000);
	autonIntake(0,0);
	stopTask(arm);
	stopTask(driveBasePID);

	//motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
	 //Vidur said he wont get mad if motors dont run later 11/3/14
}

void dropSmallPoleRed()
{
	startTask(arm);
	startTask(driveBasePID);
	drivePID(-15,-25);
	moveArmAuton(50,50);
	wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(2000);
	autonIntake(0,0);
	stopTask(arm);
	stopTask(driveBasePID);

	//motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
	 //Vidur said he wont get mad if motors dont run later 11/3/14
}

void dropSmallPoleRed()
{
	startTask(arm);
	startTask(driveBasePID);
	drivePID(-15,-25);
	moveArmAuton(50,50);
	wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(2000);
	autonIntake(0,0);
	stopTask(arm);
	stopTask(driveBasePID);

	//motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
	 //Vidur said he wont get mad if motors dont run later 11/3/14
}

void dropSmallPoleRed()
{
	startTask(arm);
	startTask(driveBasePID);
	drivePID(-15,-25);
	moveArmAuton(50,50);
	wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(2000);
	autonIntake(0,0);
	stopTask(arm);
	stopTask(driveBasePID);

	//motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
	 //Vidur said he wont get mad if motors dont run later 11/3/14
}

void dropSmallPoleRed()
{
	startTask(arm);
	startTask(driveBasePID);
	drivePID(-15,-25);
	moveArmAuton(50,50);
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
	//startTask(arm);
	//startTask(driveBasePID);
	//drivePID(-25,-15);
	drivePID(-50,-50);
	moveArmAuton(50,50);
	wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(2000);
	autonIntake(0,0);
	stopTask(arm);
	stopTask(driveBasePID);

	//motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
	 //Vidur said he wont get mad if motors dont run later 11/3/14
}
task stopAll()
{
	while(true)
{
	if (SensorValue[touchsensor] == 1)
	{
		stopTask(driveBasePID);
		motor[LB]=motor[LF]=motor[RB]=motor[RF]=0;
		stopTask(arm);
		motor[ALB]=motor[ALT]=motor[ARB]=motor[ALB]=0;
	}
}
}

void dropMediumPole()
{
	startTask(arm);
	startTask(driveBasePID);
	bool run = false;
	drivePID(15,25);
	moveArmAuton(80,80);
	wait1Msec(2000);
	autonIntake(-127,-127);
	wait1Msec(2000);
	autonIntake(0,0);


}

task usercontrol()
{
 // Remove this function call once you have "real" code.
	//startTask(arm);
	startTask(driveBasePID);
startTask(stopAll);
//	dropCube();

	//dropMediumPole();
//stopTask(arm);
	//stopTask(driveBasePID);
	//startTask(stopAll);
	//dropSmallPoleBlue();
	while (true)
	{

	//drive();

			/*
				_   _     _   _   _   _   _
			 / \ / \   / \ / \ / \ / \ / \
			( H | I ) ( V | I | D | U | R )
			 \_/ \_/   \_/ \_/ \_/ \_/ \_/
		*/
		leftArmAngle = getLeftArm();
		rightArmAngle = getRightArm();
	}
}


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

float mapRange(float a1,float a2,float b1,float b2,float s)//a1,a2 -> input range; b1,b2 -> output range; s->value input
{
    return b1 + (s-a1)*(b2-b1)/(a2-a1);
}

void moveArmAuton(float rAngle, float lAngle)
{
	left_armAngle = lAngle;
	right_armAngle = rAngle;
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

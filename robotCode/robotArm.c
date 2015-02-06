#pragma systemFile
int precisionMode = 0;
const int skyrise[7] = {1, 2, 3, 4, 5, 6, 7}; //skyrise deg values Need to set
const int post[3] = {1, 2, 3};
int skyriseIndex = 0;
//PID code
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
int lLiftModifier = -1;
float lastLiftSetPt = 0;

task armPID() {
	int armKp = 0; //Need to set
	int armKi = 0; //Need to set
	int armKd = 0; //Need to set
	while(true) {
		rAError = liftSetPt + SensorValue[rLiftEncoder] + lLiftModifier;
		lAError = liftSetPt - SensorValue[lLiftEncoder];
		lAIntegral += lAError;
		rAIntegral += rAError;
		rADerivative = rAError - rAPrevError;
		lADerivative = lAError - lAPrevError;
		motor[liftLB] = ((armKp*lAError) + (armKi*lAIntegral) + (armKd*lADerivative))/precisionMode;
		motor[liftLT] = ((armKp*lAError) + (armKi*lAIntegral) + (armKd*lADerivative))/precisionMode;
		motor[liftRB] = ((armKp*rAError) + (armKi*rAIntegral) + (armKd*rADerivative))/precisionMode;
		motor[liftRT] = ((armKp*rAError) + (armKi*rAIntegral) + (armKd*rADerivative))/precisionMode;
		if(toArmStream) {
			writeDebugStreamLine("%f, %f,",lAError, rAError);
		}
	}
}

void setArm(float deg) {
	liftSetPt = -deg;
}

bool armStopBottom() {
	return (SensorValue[liftDetectLeftBottom] || SensorValue[liftDetectRightBottom]);
}

bool armStopTop() {
	return (SensorValue[liftDetectLeftTop] || SensorValue[liftDetectRightTop]);
}

void intakeSet(float po) {
	motor[intakeL] = -po;
	motor[intakeR] = po;
}

void intakeControl() {
	if(vexRT[Btn5U])
		intakeSet(127);
	else if(vexRT[Btn5D])
		intakeSet(-127);
	else
		intakeSet(0);
}

void armControl() {
	precisionMode = vexRT[Btn8D] ? 8 : 1;
	if(vexRT[Btn6D] && !armStopBottom()) {
		setArm(SensorValue[rLiftEncoder] - 40/precisionMode);
	} else if(vexRT[Btn6U] && !armStopTop()) {
		setArm(SensorValue[rLiftEncoder] + 40/precisionMode);
	} else if(vexRT[Btn8DXmtr2] && !armStopBottom() && !armStopTop()) {
		setArm(post[0]);
	} else if(vexRT[Btn8LXmtr2] && !armStopBottom() && !armStopTop()) {
		setArm(post[1]);
	} else if(vexRT[Btn8RXmtr2] && !armStopBottom() && !armStopTop()) {
		setArm(post[2]);
	} else if(vexRT[Btn8RXmtr2] && !armStopBottom() && !armStopTop()) {
		setArm(0);
	} else if(vexRT[Btn5UXmtr2] && !armStopBottom() && !armStopTop()) {
		setArm(skyrise[skyriseIndex]);
		skyriseIndex++;
  } else {
		setArm(SensorValue[rLiftEncoder] + 1);
	}
}

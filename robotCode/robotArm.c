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

bool armStop() {
	return (liftDetectLeft || liftDetectRight);
}

void armControl() {
	precisionMode = vexRT[Btn8D] ? 8 : 1;
	if(vexRT[Btn6D] && !armStop()) {
		setArm(SensorValue[rLiftEncoder] - 40/precisionMode);
	} else if(vexRT[Btn6U]) {
		setArm(SensorValue[rLiftEncoder] + 40/precisionMode);
	} else if(vexRT[Btn8DXmtr2]) {
		setArm(post[0]);
	} else if(vexRT[Btn8LXmtr2]) {
		setArm(post[1]);
	} else if(vexRT[Btn8RXmtr2]) {
		setArm(post[2]);
	} else if(vexRT[Btn5UXmtr2]) {
		setArm(skyrise[skyriseIndex]);
		skyriseIndex++;
  } else {
		setArm(SensorValue[rLiftEncoder] + 1);
	}
}

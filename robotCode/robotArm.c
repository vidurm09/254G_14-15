int precisionMode = 0;
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

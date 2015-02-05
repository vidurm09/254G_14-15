float ignoreDriveError = 40;
float driveKp = 1.5;
float driveKi = 0.0;
float driveKd = 0.0;
bool toDriveStream = false;
float rPrevError = 0;
float rIntegral = 0;
float lPrevError = 0;
float lIntegral = 0;
float rError;
float lError;
float lDerivative;
float rDerivative;
float driveSetLPt = 0;
float driveSetRPt = 0;

task drivePID() {
	while(true) {
		rError = driveSetRPt + SensorValue[rDriveEncoder];
		lError = driveSetLPt - SensorValue[lDriveEncoder];
		lIntegral += lError;
		rIntegral += rError;
		rDerivative = rError - rPrevError;
		lDerivative = lError - lPrevError;
		motor[driveRB] = (driveKp*rError) + (driveKi*rIntegral) + (driveKd*rDerivative);
		motor[driveRF] = (driveKp*rError) + (driveKi*rIntegral) + (driveKd*rDerivative);
		motor[driveLB] = (driveKp*lError) + (driveKi*lIntegral) + (driveKd*lDerivative);
		motor[driveLF] = (driveKp*lError) + (driveKi*lIntegral) + (driveKd*lDerivative);
		if(toDriveStream) {
			writeDebugStreamLine("%f, %f,", rError, lError);
		}
	}
}

void driveTicks(float ticksL, float ticksR) {
	driveSetRPt += ticksR;
	driveSetLPt += ticksL;
}

void driveInches(float inches) {
	float ticks = (360*inches)/(PI*4);
	driveTicks(ticks, ticks);
}

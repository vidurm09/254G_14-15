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

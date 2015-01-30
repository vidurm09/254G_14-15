
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

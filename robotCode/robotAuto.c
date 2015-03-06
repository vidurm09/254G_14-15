#pragma systemFile
//All code that will run in Auto

void redSkyrise() {

}

void redPost() {
	//driveSTicks(500);

	/*setArm(30);
	intakeSet(127);
	wait1Msec(500);
	setArm(5);
	wait1Msec(500);
	intakeSet(127);
	driveStraight(180);
	wait1Msec(1000);
	//setArm(65);*/
	//driveStraig(127ht(180);
	setArm(30);
	intakeSet(127);
	wait1Msec(750);
	setArm(5);
	wait1Msec(500);
	driveStraight(550);
	setArm(120);
	wait1Msec(3000);
	setLeftTicks(685);
	SensorValue[lDriveEncoder] = 0;
	SensorValue[rDriveEncoder] = 0;
	driveStraight(-290);
	setArm(95);
	wait1Msec(1000);
	intakeSet(-127);
	SensorValue[dumpSolenoid] = 1;


}

void blueSkyrise() {

}

void bluePost() {

}

void auto() {
	resetEncoder();
	startTask(armController);
	//startTask(drivePID);
	redPost();
	//stopTask(drivePID);
}

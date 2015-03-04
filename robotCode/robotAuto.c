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
	wait1Msec(500);
	setArm(5);
	wait1Msec(500);
	driveStraight(570);
	setArm(117);
	wait1Msec(3000);
	setLeftTicks(675);
	setLeftPo(127);
	setRightPo(127);
	wait1Msec(500);
	SensorValue[lDriveEncoder] = 0;
	driveStraight(-30);
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

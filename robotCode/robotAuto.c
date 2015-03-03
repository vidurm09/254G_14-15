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
	//driveStraight(180);
	driveStraight(-360);
	driveStraight(720);
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

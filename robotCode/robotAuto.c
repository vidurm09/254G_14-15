#pragma systemFile
//All code that will run in Auto

void redSkyrise() {

}

void redPost() {
	//driveSTicks(500);
	setArm(10);
	wait10Msec(250);
	intakeSet(127);
	driveSTicks(250);
	wait1Msec(1000);
	//setArm(65);
}

void blueSkyrise() {

}

void bluePost() {

}

void auto() {
	resetEncoder();
	startTask(armController);
	startTask(drivePID);
	redPost();
	stopTask(drivePID);
}

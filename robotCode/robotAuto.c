#pragma systemFile
//All code that will run in Auto


void redSkyrise() {

}

void redPost() {
	setArm(30);
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
}

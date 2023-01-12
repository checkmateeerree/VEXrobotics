#include "main.h"

pros::ADIGyro gyro('B', 0.91);
#define horiz_speed 75

//HELPER FUNCTIONS
void setDrive(int left, int right, int horiz1,int horiz2) {

	if (abs(horiz1) > 0){
		//leftward motion
		pros::lcd::set_text(1, "works left");
		driveLeftBack = horiz_speed;
		driveLeftFront = -horiz_speed - 5;
		driveRightBack = -horiz_speed;
		driveRightFront = horiz_speed;
	}
	else if (abs(horiz2) > 0){
		//rightward motion
		pros::lcd::set_text(1, "works right");
		driveLeftBack = -horiz_speed;
		driveLeftFront = horiz_speed;
		driveRightBack = horiz_speed;
		driveRightFront = -horiz_speed - 5;
	}
	else {
		//no horizontal motion

		driveLeftBack = left;
		driveLeftFront = left;
		driveRightBack = right;
		driveRightFront = right;
	}
    
}

void resetDriveEncoders(){
	driveLeftBack.tare_position();
	driveLeftFront.tare_position();
	driveRightBack.tare_position();
	driveRightFront.tare_position();
}

double avgDriveEncoderValue() {
	return (fabs(driveLeftBack.get_position()) + 
		   fabs(driveLeftFront.get_position()) +
		   fabs(driveRightFront.get_position()) +
		   fabs(driveRightBack.get_position())) / 4;

}

//DRIVE CONTROL FUNCTIONS
void setDriveMotors() {
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	int leftButton = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
	int rightButton = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);

    if (abs(leftJoystick) < 10)
        leftJoystick = 0;
    if (abs(rightJoystick) < 10)
        rightJoystick = 0;
	
	pros::lcd::set_text(1, "uploaded");
    setDrive(leftJoystick, rightJoystick, leftButton, rightButton);
}


void translate(int units, int voltage) {
	//define direction based on units provided
	int direction = abs(units) / units; //either 1 or -1;

	//RESET MOTOR ENCODERS
	resetDriveEncoders();
	imu_sensor.reset();

	//DRIVE FORWARD TILL UNITS ARE REACHED

	while (avgDriveEncoderValue() < abs(units)){
		setDrive(voltage * direction - imu_sensor.get_rotation(), voltage * direction + imu_sensor.get_rotation(), 0, 0);
		pros::delay(10);
	}

	//BRIEF BRAKE
	setDrive(-10 * direction, -10 * direction, 0, 0);
	pros::delay(50);

	//SET DRIVE BACK TO NEUTRAL
	setDrive(0, 0, 0, 0);
}
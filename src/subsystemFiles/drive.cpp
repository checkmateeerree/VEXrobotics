#include "main.h"

pros::ADIGyro gyro('B', 0.91);
#define horiz_speed 75

//HELPER FUNCTIONS
void setDrive(int left, int right) {
	driveLeftBack = left;
	driveLeftFront = left;
	driveRightBack = right;
	driveRightFront = right;
}

void setHorizDrive(int horiz1,int horiz2){
	if (abs(horiz1) > 0){
		std::cout << "going left";
		driveLeftBack = horiz_speed;
		driveLeftFront = -horiz_speed - 5;
		driveRightBack = -horiz_speed;
		driveRightFront = horiz_speed;
	}
	if (abs(horiz2) > 0){
		std::cout << "going right";
		driveLeftBack = -horiz_speed;
		driveLeftFront = horiz_speed;
		driveRightBack = horiz_speed;
		driveRightFront = -horiz_speed - 5;
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
	
	if (abs(leftButton) > 0 || abs(rightButton) > 0){
		setHorizDrive(leftButton, rightButton);
	} else {
		//int left = leftJoystick + rightJoystick;
		//int right = leftJoystick - rightJoystick;

		//arcade
		//setDrive(left, right);
		//tank
		setDrive(leftJoystick, rightJoystick);
	}

	
}


//autonomous
void translate(int units, int voltage) {
	//define direction based on units provided
	int direction = abs(units) / units; //either 1 or -1;

	//RESET MOTOR ENCODERS
	resetDriveEncoders();
	imu_sensor.tare_rotation();

	//std::cout<< "hello";

	//DRIVE FORWARD TILL UNITS ARE REACHED

	while (avgDriveEncoderValue() < abs(units)){
		//std::cout << imu_sensor.get_rotation();
		//pros::lcd::set_text(1, std::to_string(imu_sensor.get_rotation()));
		if (direction == 1){
			setDrive(voltage * direction - imu_sensor.get_rotation(), voltage * direction + imu_sensor.get_rotation());
		} else {
			setDrive(voltage * direction + imu_sensor.get_rotation(), voltage * direction - imu_sensor.get_rotation());
		}
		
		pros::delay(10);
	}

	//BRIEF BRAKE
	setDrive(-10 * direction, -10 * direction);
	pros::delay(50);

	//SET DRIVE BACK TO NEUTRAL
	setDrive(0, 0);
}

void translateHorizontal(int units, int voltage){
	int direction = abs(units) / units;

	resetDriveEncoders();
	imu_sensor.tare_rotation();

	if (direction == 1){
			setHorizDrive(1, 0);
	} else {
		setHorizDrive(0, 1);
	}

	while (avgDriveEncoderValue() < abs(units)){
		pros::delay(10);
	}

	setHorizDrive(0, 0);
}

void rotate(int degrees, int voltage){
	//define direction, based on units provided
	int direction = abs(degrees) / degrees;
	//reset gyro
	imu_sensor.tare_rotation();
	//turn until units are reached
	setDrive(voltage * direction, -voltage * direction);
	while (fabs(imu_sensor.get_rotation()) < abs(degrees) - 5){
		//setDrive(-voltage * direction, voltage * direction, 0, 0);
		pros::delay(10);
	}

	setDrive(-voltage * direction, voltage * direction);
	//brief break
	pros::delay(100);

	//if you overshot the rotation
	if (fabs(imu_sensor.get_rotation()) > abs(degrees)){
		setDrive(0.5 * -voltage * direction, 0.5 * voltage * direction);
		while(fabs(imu_sensor.get_rotation()) > abs(degrees)){
			pros::delay(10);
		}
	}
	
	//if you undershot the rotation
	if (fabs(imu_sensor.get_rotation()) < abs(degrees)){
		setDrive(0.5 * voltage * direction, 0.5 * -voltage * direction);
		while(fabs(imu_sensor.get_rotation()) > abs(degrees)){
			pros::delay(10);
		}
	}

	//setDrive(10 * direction, -10 * direction, 0, 0);
	//reset drive to zero
	setDrive(0, 0);
}
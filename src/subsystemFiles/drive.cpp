#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right) {
    driveLeftBack = left;
    driveLeftFront = left;
    driveRightBack = right;
    driveRightBack = right;
}

//DRIVE CONTROL FUNCTIONS
void setDriveMotors() {
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    if (abs(leftJoystick) < 10)
        leftJoystick = 0;
    if (abs(rightJoystick) < 10)
        rightJoystick = 0;
    setDrive(leftJoystick, rightJoystick);
}

/*	int power = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
		int left = power + turn;
		int right = power - turn;
		left_wheels.move(left);
		right_wheels.move(right);

		if (master.get_digital(DIGITAL_R1)) {
			shooterLeft.move(12000); 
			shooterRight.move(12000);
		}
		else if (master.get_digital(DIGITAL_R2)) {
			shooterLeft.move(-12000);
			shooterRight.move(-12000);
		}
		else {
			shooterLeft.move_velocity(0);
			shooterRight.move_velocity(0);
			
		}*/



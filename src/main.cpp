#include <string>
#include "main.h"
#include "pros/motors.h"
using namespace std;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "yo whats good");

	driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	//intakeRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	shifter.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	shooter.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	imu_sensor.reset();

	vision_sensor.clear_led();

	pros::vision_signature_s_t RED_SIG = 
		pros::Vision::signature_from_utility(1, 7631, 10241, 8936, -1921, -353, -1138, 3.000, 0);
	pros::vision_signature_s_t BLUE_SIG = 
		pros::Vision::signature_from_utility(2, -2897, -1939, -2418, 10493, 13335, 11914, 3.000, 0);
	pros::vision_signature_s_t YELLOW_SIG = 
		pros::Vision::signature_from_utility(3, 1655, 2063, 1859, -4605, -4257, -4431, 3.000, 0);
	//vision::signature SIG_1 (1, 7631, 10241, 8936, -1921, -353, -1138, 3.000, 0); vision::signature SIG_2 (2, -2897, -1939, -2418, 10493, 13335, 11914, 3.000, 0); vision::signature SIG_3 (3, 1655, 2063, 1859, -4605, -4257, -4431, 3.000, 0); vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 3.000, 0); vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 3.000, 0); vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 3.000, 0); vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 3.000, 0); vex::vision vision1 ( vex::PORT1, 50, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7 );

	vision_sensor.set_signature(1, &RED_SIG);
	vision_sensor.set_signature(2, &BLUE_SIG);
	vision_sensor.set_signature(3, &YELLOW_SIG);
	
	pros::delay(2000);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonShoot(){
	//shoots two discs into low goal
	setShooter(127);
	pros::delay(2500);
	for (int i = 0; i < 2; i++){
		setShifter(70);
		pros::delay(300);
		setShifter(-70);
		pros::delay(300);
	}
	setShooter(0);
	setShifter(0);
}

void spinRoller(){
	//spins the roller 

	setDrive(50, 50);
	//translate(300, 70);
	pros::delay(100);
	//spin roller
	setIntake(-127);
	pros::delay(1000);
	setIntake(0);

	setDrive(0, 0);
	pros::delay(10);
}


void blueLeftCorner(){
	//robot allowed to be in front of roller
	//permute to roller
	spinRoller();
	pros::delay(10);
	//back up
	translate(-100, 70);
	pros::delay(50);
	//rotate it
	rotate(90, 60);
	translate(-200, 70);

	autonShoot();
	//translateHorizontal(500, 50);
	//positive is left, negative is right
}

void redRightCorner(){
	autonShoot();

	pros::delay(100);
	rotate(90, 60);

	pros::delay(100);
	translateHorizontal(-1000, 80);
	pros::delay(300);
	spinRoller();
	//setIntake(100);
}

void redLeftCorner(){
	//robot allowed to be in front of roller
	//permute to roller
	spinRoller();
	//back up
	translate(-100, 70);
	pros::delay(50);
	//rotate it
	rotate(90, 60);
	translate(-200, 70);

	autonShoot();

	//translateHorizontal(500, 50);
	
	//positive is left, negative is right
}

void blueRightCorner(){
	autonShoot();

	pros::delay(100);
	rotate(90, 60);

	pros::delay(100);
	translateHorizontal(-1000, 80);
	pros::delay(300);
	spinRoller();

}


void autonomous() {
	//redLeftCorner();
	//redRightCorner();
	blueRightCorner();
	//blueLeftCorner();

	/*pros::ADIDigitalOut piston ('H');

	piston.set_value(true);
	pros::delay(1000);
	piston.set_value(false);*/
	//pros::lcd::set_text(1, "ran auto");
	return;
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	//autonomous();
	
	while (true){
		setDriveMotors();
		setIntakeMotors();
		setShootMotor();
		setShiftMotor();

		pros::delay(10);
		//pros::delay(1000);
	}
}	


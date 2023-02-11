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


	//
	//pros::ADIDigitalOut piston ('H');
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
		pros::Vision::signature_from_utility(2, -2383, -717, -1550, 4885, 9151, 7018, 1.000, 0);
	pros::vision_signature_s_t YELLOW_SIG = 
		pros::Vision::signature_from_utility(3, 1761, 2361, 2061, -4491, -3969, -4230, 3.000, 0);
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
	alignRobot();
	setShooter(127);
	pros::delay(3500);
	for (int i = 0; i < 2; i++){
		setShifter(127);
		pros::delay(300);
		setShifter(-70);
		alignRobot();
		pros::delay(500);
		
	}
	setShooter(0);
	setShifter(0);
}

void spinRoller(int time){
	//spins the roller 

	setDrive(50, 50);
	//translate(300, 70);
	pros::delay(100);

	setIntake(-100);

	/*double hue_value = optical_sensor.get_hue();
        std::cout << hue_value << std::endl;
        setDrive(50, 50);
        if ((hue_value > 20) && (hue_value < 210 || hue_value > 220)){
            setIntake(-90);
        }
        if (isRed){
            while(hue_value > 20){
                hue_value = optical_sensor.get_hue();
                pros::delay(10);
            }
        }
        else{
            while(hue_value < 210 || hue_value > 220){
                hue_value = optical_sensor.get_hue();
                pros::delay(10);
            }
        }
*/
	pros::delay(time);
	
	setIntake(0);

	setDrive(0, 0);
	pros::delay(10);
}


void blueLeftCorner(){
	isRed = false;
	//robot allowed to be in front of roller
	//permute to roller
	spinRoller(200);
	//back up
	translate(-100, 70);
	pros::delay(50);
	//rotate it
	//rotate(-90, 60);
	translate(-200, 70);
	pros::delay(100);
	translateHorizontal(-1000, 80);
	pros::delay(100);
	translate(-300, 80);
	pros::delay(100);

	rotate(-30, 80);

	autonShoot();

	//translateHorizontal(500, 50);
	
	//positive is left, negative is right
}

void redRightCorner(){
	isRed = true;
	translateHorizontal(-1000, 80);
	pros::delay(300);
	spinRoller(200);
	translate(-300, 80);
	autonShoot();

	
	//setIntake(100);
}

void redLeftCorner(){
	isRed = true;
	//robot allowed to be in front of roller
	//permute to roller
	spinRoller(200);
	//back up
	translate(-100, 70);
	pros::delay(50);
	//rotate it
	//rotate(-90, 60);
	translate(-200, 70);
	pros::delay(100);
	translateHorizontal(-1000, 80);
	pros::delay(100);
	translate(-300, 80);
	pros::delay(100);

	rotate(-30, 80);

	autonShoot();

	//translateHorizontal(500, 50);
	
	//positive is left, negative is right
}

void blueRightCorner(){
	isRed = false;
	autonShoot();

	pros::delay(100);
	rotate(90, 60);

	pros::delay(100);
	translateHorizontal(-1000, 80);
	pros::delay(300);
	spinRoller(200);

}

void progSkills() {
	isRed = true;
	redLeftCorner();
	
	pros::delay(300);

	//get second roller
	translate(-200, 80);
	rotate(105, 80);

	translate(2500, 80);

	spinRoller(300);
	pros::delay(300);

	translate(-1000, 80);
	pros::delay(100);
	rotate(-55, 80);
	pros::delay(100);

	//go to other side of field
	translate(-10000, 100);
	pros::delay(100);
	translate(1000, 100);
	pros::delay(100);
	rotate(120, 80);

	translate(1000, 80);
	spinRoller(300);

	translate(-1200, 80);

	rotate(105, 80);
	translate(1000, 80);
	spinRoller(300);
	
	//if more time intake more discs and shoot



/*	piston1.set_value(true);
	piston2.set_value(true);
	pros::delay(1000);*/


}


void autonomous() {
	//redLeftCorner();
	//redRightCorner();
	//blueRightCorner();
	//blueLeftCorner();

	//translateHorizontal(-2000, 80);

	blueLeftCorner();

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

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) > 0 && controller.get_digital(DIGITAL_R1)){
			piston1.set_value(true);
			piston2.set_value(true);
			translate(1000, 80);
		}

		pros::delay(10);
		//pros::delay(1000);
	}
}	


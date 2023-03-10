#include "main.h"

#define SHIFTER_PORT 1
#define SHOOTER_PORT 2
#define INTAKE_PORT 3
#define DRIVE_LEFT_BACK_PORT 5
#define DRIVE_LEFT_FRONT_PORT 6
#define DRIVE_RIGHT_BACK_PORT 7
#define DRIVE_RIGHT_FRONT_PORT 8
#define IMU_PORT 10
#define VISION_PORT 20
#define OPTICAL_PORT 17
#define DISTANCE_PORT 19

//MOTORS
pros::Motor shifter(SHIFTER_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor shooter(SHOOTER_PORT, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake(INTAKE_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
//pros::Motor intakeRight(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(DRIVE_LEFT_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftFront(DRIVE_LEFT_FRONT_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(DRIVE_RIGHT_BACK_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(DRIVE_RIGHT_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//SENSORS
pros::Imu imu_sensor(IMU_PORT);
pros::Vision vision_sensor(VISION_PORT);
pros::Optical optical_sensor(OPTICAL_PORT);
pros::Distance distance_sensor(DISTANCE_PORT);
pros::ADIDigitalOut piston1 ('A');
pros::ADIDigitalOut piston2 ('H');
bool isRed = false;
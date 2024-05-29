#include "main.h"

#define SHIFTER_PORT 18
#define SHOOTER1_PORT 3
#define SHOOTER2_PORT 10
#define INTAKE_PORT 4
#define DRIVE_LEFT_BACK_PORT 7
#define DRIVE_LEFT_FRONT_PORT 5

#define DRIVE_RIGHT_BACK_PORT 8
#define DRIVE_RIGHT_FRONT_PORT 6

#define VISION_PORT 20
#define OPTICAL_PORT 13
#define DISTANCE_PORT 19
#define IMU_PORT 2
#define ROTATION_PORT 11

//MOTORS
pros::Motor shifter(SHIFTER_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor shooter1(SHOOTER1_PORT, MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor shooter2(SHOOTER2_PORT, MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_COUNTS);
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
pros::Rotation rotation_sensor(ROTATION_PORT);
pros::ADIDigitalOut piston1 ('A');
pros::ADIDigitalOut piston2 ('H');
bool isRed = false;
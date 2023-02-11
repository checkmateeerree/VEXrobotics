//motors, controllers, things we want globalized
#pragma
#include "main.h"

//MOOTRS
extern pros::Motor shifter;
extern pros::Motor shooter;
extern pros::Motor intake;
//extern pros::Motor intakeRight;
extern pros::Motor driveLeftBack;
extern pros::Motor driveLeftFront;
extern pros::Motor driveRightBack;
extern pros::Motor driveRightFront;


//CONTROLLER
extern pros::Controller controller;

//MISCELLANEOUS/sensors
extern pros::Imu imu_sensor;
extern pros::Vision vision_sensor;
extern pros::Optical optical_sensor;
extern pros::Distance distance_sensor;
extern bool isRed;
extern pros::ADIDigitalOut piston1;
extern pros::ADIDigitalOut piston2;
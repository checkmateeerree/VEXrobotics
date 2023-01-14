#pragma
#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right);
void setHorizDrive(int horiz1, int horiz2);
void resetDriveEncoders();
double avgDriveEncoderValue();

//DRIVE CONTROL FUNCTIONS
void setDriveMotors();

//AUTNONOMOUS FUNCTIONS
void translate(int units, int voltage);
void translateHorizontal(int units, int voltage);
void rotate(int degrees, int voltage);

#include "main.h"

//HELPER FUNCTIONS
void setShifter(int power){
    shooter = power;
}

//DRIVER CONTROL FUNCTIONS
void setShiftMotor(){
    //bottom trigger intakes, top trigger outtakes
    int shooterPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
    setShooter(shooterPower);
}
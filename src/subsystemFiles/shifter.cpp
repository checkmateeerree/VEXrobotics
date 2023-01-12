#include "main.h"

//HELPER FUNCTIONS
void setShifter(int power){
    shifter = power;
}

//DRIVER CONTROL FUNCTIONS
void setShiftMotor(){
    //bottom trigger intakes, top trigger outtakes
    int shifterPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
    setShifter(shifterPower);
}
#include "main.h"

//HELPER FUNCTIONS
void setShifter(int power){
    shifter = power;
}

//DRIVER CONTROL FUNCTIONS
void setShiftMotor(){
    //bottom trigger intakes, top trigger outtakes
    int shifterPower = 90 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_B));
    setShifter(shifterPower);

    //automated shift
    if (abs(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) > 0) {
        setShifter(90);
        //setShifter(0);
        pros::delay(100);
        setShifter(-90);
        pros::delay(100);
    }
}
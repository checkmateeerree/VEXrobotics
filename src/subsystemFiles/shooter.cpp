#include "main.h"

//HELPER FUNCTIONS
void setShooter(int power){
    shooter = power;
    //shooter2 = power;
}

bool isToggled = false;

//DRIVER CONTROL FUNCTIONS
void setShootMotor(){
    //bottom trigger intakes, top trigger outtakes
    int buttonVal = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
    int shooterPower = 90 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));

    if (buttonVal > 0 && isToggled){
        //if button is being pressed and
        //toggle is already true
        isToggled = false;
    } else if (buttonVal > 0 && !isToggled){
        //if button is not being pressed
        //and toggle is not true
        isToggled = true;
    }

    if (isToggled){
        setShooter(80);
    } else {
        setShooter(shooterPower);
    }
}


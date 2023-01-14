#include "main.h"

//HELPER FUNCTIONS
void setShooter(int power){
    shooter = power;
    //shooter2 = power;
}

//DRIVER CONTROL FUNCTIONS
void setShootMotor(){
    //bottom trigger intakes, top trigger outtakes
    int shooterPower = 100 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));
    setShooter(shooterPower);
}


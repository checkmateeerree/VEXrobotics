#include "main.h"

//HELPER FUNCTIONS
void setIntake(int power){
    intake = power;
    //intakeRight = power;
}

//DRIVER CONTROL FUNCTIONS
void setIntakeMotors(){
    //bottom trigger intakes, top trigger outtakes
    int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
    int rollerToggle = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
    if (rollerToggle > 0){
        setIntake(90);
	    /*double hue_value = optical_sensor.get_hue();
        std::cout << hue_value << std::endl;
        setDrive(50, 50);
        if ((hue_value > 20) && (hue_value < 210 || hue_value > 220)){
            setIntake(-90);
        }
        if (isRed){
            while(hue_value > 20){
                int kill = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
                if (kill > 0) break;
                hue_value = optical_sensor.get_hue();
                pros::delay(10);
            }
        }
        else{
            while(hue_value < 210 || hue_value > 220){
                int kill = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
                if (kill > 0) break;
                hue_value = optical_sensor.get_hue();
                pros::delay(10);
            }
        }

        pros::delay(300);
        
        setIntake(0);
        setDrive(0, 0);*/
    }
    else {
        setIntake(intakePower);
    }
}


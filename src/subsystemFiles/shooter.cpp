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
    int alignButton = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

    if (buttonVal > 0 && isToggled){
        //if button is being pressed and
        //toggle is already true
        isToggled = false;
    } else if (buttonVal > 0 && !isToggled){
        //if button is not being pressed
        //and toggle is not true
        isToggled = true;
    }

    if (alignButton > 0){
        //cout << "hji" << endl;
        alignRobot();
    }
    
    if (isToggled || shooterPower > 0){
        //try detect blue
        setShooter(127);
    } 
    else {
        setShooter(0);
    }
}

int alignRobot(){
    int sigToRead = -1;
    if (isRed) sigToRead = 1;
    else sigToRead = 2;
    pros::vision_object_s_t high_goal = vision_sensor.get_by_sig(0, sigToRead);

    pros::lcd::set_text(2, std::to_string(sigToRead));
    pros::lcd::set_text(3, std::to_string(high_goal.width));
    pros::lcd::set_text(5, std::to_string(high_goal.signature));
    pros::lcd::set_text(4, std::to_string(high_goal.left_coord));
    pros::lcd::set_text(6, std::to_string(high_goal.height));

    std::cout << high_goal.signature << std::endl;
    //high goal not blue or red
    if (high_goal.signature != 1 && high_goal.signature != 2) return -1;

    std::cout << high_goal.left_coord << std::endl;

    if (high_goal.signature == 1 && isRed){
        //red
        std::cout<<high_goal.left_coord << std::endl;
        if (high_goal.left_coord > 135){
            //too far left
            setDrive(40, -40);
            
            while (high_goal.left_coord > 135){
                high_goal = vision_sensor.get_by_sig(0, sigToRead);
                pros::delay(10);
            }
            //beat coast
            setDrive(-10, 10);
            pros::delay(100);
            setDrive(0, 0);
        } else if (high_goal.left_coord < 125){
            //too far right
            setDrive(-40, 40);
            while (high_goal.left_coord < 125){
                high_goal = vision_sensor.get_by_sig(0, sigToRead);
                pros::delay(10);
            }
            setDrive(10, -10);
            pros::delay(100);
            setDrive(0, 0);
        }
    }

    
    else if (high_goal.signature == 2 && !isRed) {
        //blue
        pros::lcd::set_text(0, "is blue");
        if (high_goal.left_coord > 140){
            //too far left
            setDrive(40, -40);
            
            while (high_goal.left_coord > 140){
                high_goal = vision_sensor.get_by_sig(0, sigToRead);
                pros::delay(10);
            }
            //beat coast
            setDrive(10, -10);
            pros::delay(100);
            setDrive(0, 0);
        } else if (high_goal.left_coord < 120){
            //too far right
            setDrive(-40, 40);
            while (high_goal.left_coord < 120){
                high_goal = vision_sensor.get_by_sig(0, sigToRead);
                pros::delay(10);
            }
            setDrive(10, -10);
            pros::delay(100);
            setDrive(0, 0);
        }

    }

   // 
   return high_goal.width;

}

int findDist(){
    return distance_sensor.get();
}

int roundNum(int num)
{
     int rem = num % 10;
     return rem >= 5 ? (num - rem + 10) : (num - rem);
}
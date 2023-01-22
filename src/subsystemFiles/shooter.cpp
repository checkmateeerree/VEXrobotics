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
    if (isToggled || shooterPower > 0){
        //setShooter(90);

        int width = alignRobot();
        int dist = findDist();

        if (width != -1){
            setShooter(100 + 60 - roundNum(width));
            //width 60: 90 good
            //width 70: 
        } else {
            setShooter(90);
        }
            //automatic set shooter
        

    } 
    else {
        setShooter(0);
    }
      
}

int alignRobot(){
    pros::vision_object_s_t object_arr[1];
    vision_sensor.read_by_sig(0, 1 ? isRed : 2, 1, object_arr);

    pros::vision_object_s_t high_goal = object_arr[0];

    int dist = findDist();

    pros::lcd::set_text(3, std::to_string(high_goal.width));
    pros::lcd::set_text(4, std::to_string(dist));
    pros::lcd::set_text(7, std::to_string(high_goal.left_coord));
    pros::lcd::set_text(5, std::to_string(high_goal.x_middle_coord));
    pros::lcd::set_text(6, std::to_string(high_goal.y_middle_coord));

    std::cout << high_goal.signature << std::endl;
    //high goal not blue or red
    if (high_goal.signature != 1 && high_goal.signature != 2) return -1;

    std::cout << high_goal.left_coord << std::endl;

    if (high_goal.signature == 1 && isRed){
        //red
        std::cout<<high_goal.left_coord << std::endl;
        if (high_goal.left_coord > 110){
            //too far left
            setDrive(40, -40);
            
            while (high_goal.left_coord > 110){
                vision_sensor.read_by_size(0, 1, object_arr);
                high_goal = object_arr[0];
                pros::delay(10);
            }
            //beat coast
            setDrive(-10, 10);
            pros::delay(100);
            setDrive(0, 0);
        } else if (high_goal.left_coord < 90){
            //too far right
            setDrive(-40, 40);
            while (high_goal.left_coord < 90){
                vision_sensor.read_by_size(0, 1, object_arr);
                high_goal = object_arr[0];
                pros::delay(10);
            }
            setDrive(10, -10);
            pros::delay(100);
            setDrive(0, 0);
        }
    }
    else if (high_goal.signature == 2 && !isRed) {
        //blue


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
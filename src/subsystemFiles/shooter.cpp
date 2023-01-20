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
    pros::vision_object_s_t object_arr[1];
    vision_sensor.read_by_size(0, 1, object_arr);

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
        setShooter(90);

        if (object_arr[0].signature == 1 || object_arr[0].signature == 2){
            int width = alignRobot(object_arr);
            //automatic set shooter
            
        }

    } 
    else {
        setShooter(0);
    }
      
}

int alignRobot(pros::vision_object_s_t object_arr[1]){
    pros::vision_object_s_t high_goal = object_arr[0];

    pros::lcd::set_text(3, std::to_string(high_goal.width));
    pros::lcd::set_text(4, std::to_string(high_goal.width));
    pros::lcd::set_text(5, std::to_string(high_goal.x_middle_coord));
    pros::lcd::set_text(6, std::to_string(high_goal.y_middle_coord));

    std::cout << high_goal.signature << std::endl;
    //high goal not blue or red
    if (high_goal.signature != 1 && high_goal.signature != 2) return;

    std::cout << high_goal.left_coord << std::endl;

    if (high_goal.signature == 1){
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
    else {
        //blue
    }

   // 
   return high_goal.width;

}

int findDist(){
    return distance_sensor.get();
}
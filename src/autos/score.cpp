#include "autos.hpp"
#include "config.h"
#include "pros/rtos.hpp"

void score(int time, int x_cord, int y_cord, int heading){
    
    //reverse motors to line up with goal
    AllMotors.move(-60);
    intake.move(127);

    //delay for selected time
    pros::delay(time);
    intake.move(0);
    AllMotors.move(0);

    //set pose after delay to be lined up hopefully
    chassis.setPose(x_cord,y_cord,heading);

}
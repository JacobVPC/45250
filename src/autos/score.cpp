#include "autos.hpp"
#include "config.h"
#include "pros/rtos.hpp"

void score(double time,double x_cord,double y_cord,double heading){
    
    //reverse motors to line up with goal
    
    intake.move(127);
    AllMotors.move(-120);

    //delay for selected time
    pros::delay(time*1000);
    intake.move(0);
    AllMotors.move(0);

    //set pose after delay to be lined up hopefully
    chassis.setPose(x_cord,y_cord,heading);

}
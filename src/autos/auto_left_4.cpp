#include "autos.hpp"
#include "config.h"
#include <cmath>
#include "pros/rtos.hpp"



void auto_left_4(){
    wing.set_value(true);
    mid_goal.set_value(false);
    
    chassis.setPose(0,0,0);

    firstStage.move(127);
    secondStage.move(-40);



    chassis.moveToPoint(-8.8, 35.2, 2000,{.minSpeed = 50, .earlyExitRange =10});
    pros::delay(500);
    scraper.set_value(true);
    
    chassis.moveToPoint(-26, 0, 2000,{.minSpeed = 50, .earlyExitRange =15});
    chassis.moveToPoint(-40, 0, 1500,{.minSpeed = 50, .earlyExitRange = 5});
    

    chassis.moveToPoint(-36, 22.3, 1000,{.forwards = false});
    scraper.set_value(false);
    chassis.waitUntilDone();
    score(2, -32, 17.3, 180);

    chassis.moveToPoint(-41, 8, 1000,{.minSpeed = 50, .earlyExitRange =2});
    chassis.moveToPoint(-55, 36, 2000,{.forwards = false});
    

}
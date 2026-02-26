#include "autos.hpp"
#include "config.h"
#include "dsr.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"

void auto_left_counter(){
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
    
    chassis.waitUntilDone();
    score(2, -32, 17.3, 180);

    chassis.moveToPoint(-32, -14, 1700);
    firstStage.move(127);
    chassis.waitUntilDone();
    scraper.set_value(false);

    chassis.moveToPoint(9, 35.5, 1500,{.forwards = false});
    chassis.waitUntilDone();

    mid_goal.set_value(true);
    pros::delay(2000);

    //descore

    wing.set_value(true);
    chassis.moveToPoint(-20, 11, 1000,{.minSpeed = 50,.earlyExitRange = 5});
    chassis.moveToPoint(-12, 34, 1000,{.minSpeed = 50,.earlyExitRange = 1});
    chassis.moveToPoint(-13, 40, 1000);
}
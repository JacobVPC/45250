#include "autos.hpp"
#include "config.h"
#include <cmath>



void auto_left_9(){
    wing.set_value(true);
    scraper.set_value(false);
    chassis.setPose(0,0,0);

    firstStage.move(127);
    
    //5 blocks
    chassis.moveToPoint(0, 20, 2000,{.minSpeed = 70, .earlyExitRange = 14});
    chassis.moveToPoint(-29, 42.5, 2000);
    chassis.waitUntilDone();

    //middle goal
    chassis.moveToPoint(-3, 30, 1000,{.forwards = false});
    
    chassis.moveToPose(5.5, 42,-132, 1000,{.forwards = false});
    pros::delay(500);
    wing.set_value(false);
    pros::delay(1200);
    firstStage.move(0);
    wing.set_value(true);

    //goal
    chassis.moveToPoint(-36, 3, 1500);
    chassis.moveToPoint(-36, 23.5, 1000,{.forwards = false});
    chassis.waitUntilDone();
    intake.move(127);
    scraper.set_value(true);
    leftMotors.move(-80);
    rightMotors.move(-80);
    pros::delay(1600);

    
    chassis.setPose(-36,23.5 ,180);
    firstStage.move(127);

    //matchloader
    chassis.moveToPoint(-36, -7, 1000);
    pros::delay(1500);
    chassis.moveToPoint(-36, 23.5, 1000,{.forwards=false});

    chassis.waitUntilDone();
    intake.move(127);
    leftMotors.move(-70);
    rightMotors.move(-70);
    pros::delay(1300);
    intake.move(0);
    scraper.set_value(false);


}   

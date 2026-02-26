#include "autos.hpp"
#include "config.h"
#include "dsr.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"

void auto_right_7(){

    wing.set_value(true);
    mid_goal.set_value(false);
    
    chassis.setPose(0,0,0);

    firstStage.move(127);
    secondStage.move(-40);



    chassis.moveToPoint(8.8, 35.2, 2000,{.minSpeed = 50, .earlyExitRange =10});
    pros::delay(500);
    scraper.set_value(true);
    
    chassis.moveToPoint(26, 0, 2000,{.minSpeed = 50, .earlyExitRange = 15});
    chassis.moveToPoint(36, 0, 1500,{.minSpeed = 50, .earlyExitRange = 5});
    

    chassis.moveToPoint(34, -14, 1000);
    chassis.waitUntilDone();



    //global position reset after matchload.
    ResetPose(
    frontDistanceSensor, BackWallAngle, -72, false,
    leftDistanceSensor, RightWallAngle, -72, true);

    chassis.moveToPoint(48, -28.5, 1300,{.forwards = false});
    chassis.waitUntilDone();
    scraper.set_value(false);


    //goes back to pure pursuit since its aligned with goal.
    score(4, 32, 17.3, 180);

    chassis.moveToPoint(41, 8, 1000,{.minSpeed = 50, .earlyExitRange =2});
    chassis.moveToPoint(41, 36, 2000);
    

}
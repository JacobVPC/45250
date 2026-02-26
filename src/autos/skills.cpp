#include "autos.hpp"
#include "config.h"
#include "dsr.hpp"
#include "pros/rtos.hpp"

void skills(){
    
    // mid_goal.set_value(false);
    // scraper.set_value(false);
    
    
    // firstStage.move(127);
    // secondStage.move(-60);

    // //going into park zone
    // AllMotors.move(60);
    // pros::delay(500);
    // AllMotors.move(0);
    // pros::delay(1500);


    // AllMotors.move(127);
    // pros::delay(1000);
    // AllMotors.move(-30);
    // pros::delay(600);
    // AllMotors.move(127);
    // pros::delay(1000);

    // //leaving
    // AllMotors.move(-100);
    // pros::delay(500);
    // AllMotors.move(0);
    // pros::delay(1500);
    // AllMotors.move(30);
    // pros::delay(2500);
    // AllMotors.move(0);

    // scraper.set_value(true);
    // pros::delay(300);
    // ResetPose(
    // frontDistanceSensor, BackWallAngle, -72, false,
    // rightDistanceSensor, LeftWallAngle, -72, true);

    // scraper.set_value(false);
    wing.set_value(false);
    chassis.setPose(0,-46,180);
    chassis.moveToPoint(0, -20, 1500,{.forwards = false});
   

    firstStage.move(127);
    chassis.moveToPoint(-17, -20, 1000);


    chassis.moveToPose(-10, -10, 220,2000,{.forwards = false});
    chassis.waitUntilDone();
    firstStage.move(-127);
    pros::delay(300);
    firstStage.move(100);
    mid_goal.set_value(true);

    pros::delay(4000);
    firstStage.move(127);
    mid_goal.set_value(false);
    
    chassis.moveToPoint(-44, -43,  1000);
    chassis.waitUntilDone();
    scraper.set_value(true);

    ResetPose(
    frontDistanceSensor, LeftWallAngle, -72, true,
    leftDistanceSensor, BackWallAngle, -72, false);

    chassis.moveToPoint(-43, -70, 1000);
    chassis.waitUntilDone();
    pros::delay(2500);

    chassis.moveToPoint(-58, -27, 1500,{.forwards = false, . minSpeed = 50, .earlyExitRange = 5});
    scraper.set_value(false);
    chassis.moveToPoint(-55, 47, 2000,{.forwards = false});

    chassis.moveToPoint(-38, 47, 1000);
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();

    score(3, 0, 0, 0);
    scraper.set_value(true);
    pros ::delay(300);

    ResetPose(frontDistanceSensor, FrontWallAngle, 72, false,
              leftDistanceSensor, LeftWallAngle, -72, true);


    



}
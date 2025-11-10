#include "autos.hpp"
#include "config.h"
#include "pros/rtos.hpp"

void auto_awp(){

    chassis.setPose(0,0,0);


    //push alliance
    chassis.moveToPoint(0, -6, 1000,{.forwards = false});
    chassis.moveToPose(0, 0, 0, 1000);

    //x -0.1
    chassis.moveToPoint(0, 46, 3000);
    chassis.waitUntilDone();

    //x 4.1 for some reason?
    chassis.turnToPoint(9.9, 46, 1000);

    //matchloader
    scraper.set_value(true);
    chassis.moveToPoint(9.9, 46, 1000);
    firstStage.move(127);
    pros::delay(1300);
    firstStage.move(0);

    //first goal
    chassis.moveToPoint(-19.4, 46, 1500,{.forwards = false});
    chassis.waitUntilDone();
    intake.move(127);
    leftMotors.move(-30);
    rightMotors.move(-30);
    pros::delay(1200);
    intake.move(0);
    leftMotors.move(0);
    rightMotors.move(0);
    


}

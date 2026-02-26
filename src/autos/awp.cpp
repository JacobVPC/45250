#include "autos.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"


void auto_awp(){

    chassis.setPose(0,0,90);

    //first ml
    chassis.moveToPoint(36, 0, 2000,{.minSpeed = 50,.earlyExitRange = 15});

    scraper.set_value(true);
    chassis.turnToHeading(190, 1000,{.minSpeed = 50,.earlyExitRange = 10});
    chassis.moveToPoint(32, -18, 1000);

    //load 3 blocks
    firstStage.move(127);
    pros::delay(1500);

    //score 4
    chassis.moveToPoint(32, 20, 1000,{.forwards = false});
    chassis.waitUntilDone();
    scraper.set_value(false);
    score(1.5, 32, 20, 180);
    

    //6 blocks
    chassis.swingToHeading(320, lemlib::DriveSide::RIGHT, 1000,{.minSpeed=50, .earlyExitRange = 10});
    
    //3
    firstStage.move(127);
    chassis.moveToPoint(4.5, 27, 1000,{.minSpeed=50,.earlyExitRange = 1});
    pros::delay(200);
    scraper.set_value(true);
    

    chassis.moveToPoint(-23, 26, 3000,{.minSpeed=50,.earlyExitRange =1});
    scraper.set_value(false);
    firstStage.move(0);
    
    chassis.moveToPoint(-43, 27.5, 3000,{.minSpeed=50,.earlyExitRange = 1});
    scraper.set_value(true);
    firstStage.move(127);

    //middle
   
    chassis.moveToPoint(-23, 40, 1500,{.forwards=false});
    chassis.waitUntilDone();
    mid_goal.set_value(true);
    intake.move(-127);
    pros::delay(150);
    intake.move(0);
    pros::delay(10);
    firstStage.move(127);
    pros::delay(1000);
    mid_goal.set_value(false);


    //go to second ml

    chassis.moveToPoint(-65, 0, 3000,{.minSpeed = 50, .earlyExitRange = 15});
    chassis.moveToPoint(-63, -18, 1000);
    pros::delay(1300);

    //score 
    chassis.moveToPoint(-63, 20, 1000,{.forwards = false});
    score(3000, -63, 20, 0);


    


    
}
#include "autos.hpp"
#include "config.h"
#include "pros/rtos.hpp"

void skills(){
    chassis.setPose(0,0,90);

    chassis.moveToPoint(50, 0, 1500);
    chassis.turnToHeading(180, 1000);
    
    //matchload
    scraper.set_value(true);
    secondStage.move(-80);
    firstStage.move(127);
    chassis.moveToPoint(50,-18, 2000);
    pros::delay(3000);
    scraper.set_value(false);

    secondStage.move(0);
    firstStage.move(0);

    //go to second ML
    chassis.moveToPoint(67, 26, 2000,{.forwards = false , .minSpeed = 60, .earlyExitRange = 15});
    chassis.moveToPoint(66, 91, 2000,{.forwards = false});
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(49, 91, 1000);

    //score
    chassis.moveToPoint(49, 79,1000,{.forwards= false});
    scraper.set_value(true);
    chassis.waitUntilDone();
    
    AllMotors.move(-90);
    intake.move(127);
    pros::delay(4000);
    AllMotors.move(0);
    intake.move(0);
    chassis.setPose(49,79,0);

    //second ML
    chassis.moveToPoint(49, 110, 1000);
    firstStage.move(127);
    pros::delay(3000);
    scraper.set_value(false);
 

    //score
    chassis.moveToPoint(49, 79, 1000,{.forwards = false});
    chassis.waitUntilDone();
    AllMotors.move(-90);
    intake.move(127);
    pros::delay(4000);
    AllMotors.move(0);
    intake.move(0);
    chassis.setPose(49,79,0);

    //move to third ML
    chassis.turnToHeading(-90, 1000);
    chassis.moveToPoint(-50, 92, 2000);
    chassis.turnToHeading(0, 2000);
    scraper.set_value(true);

    //third ML
    chassis.moveToPoint(-50, 115, 1000);
    firstStage.move(127);
    pros::delay(3000);
    scraper.set_value(false);

    //go to ML 4
    chassis.moveToPoint(-67, 76, 2000,{.forwards = false , .minSpeed = 60, .earlyExitRange = 15});
    chassis.moveToPoint(-66, 10, 2000,{.forwards = false});
    chassis.turnToHeading(90, 1000);
    chassis.moveToPoint(-50, 10, 1000);
    chassis.turnToHeading(180, 1000);
    scraper.set_value(true);

    // //Score 
    chassis.moveToPoint(-50, 20, 1500,{.forwards = false});
    chassis.waitUntilDone();
    AllMotors.move(-90);
    intake.move(127);
    pros::delay(4000);
    AllMotors.move(0);
    intake.move(0);
    chassis.setPose(-50,20,180);

    //ML 4
    chassis.moveToPoint(-50, -12, 2000);
    firstStage.move(127);
    pros::delay(3000);
    scraper.set_value(false);

    //Score 
    chassis.moveToPoint(-50, 20, 1500,{.forwards = false});
    chassis.waitUntilDone();
    AllMotors.move(-90);
    intake.move(127);
    pros::delay(4000);
    AllMotors.move(0);
    intake.move(0);
    chassis.setPose(-50,20,180);

    //park
    intake.move(127);
    chassis.moveToPoint(-50, -12, 2000,{.minSpeed = 60, .earlyExitRange = 27});
    chassis.moveToPoint(20, -18, 2000,{.minSpeed = 127});
    


}
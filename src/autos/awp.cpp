#include "autos.hpp"
#include "config.h"
#include "pros/rtos.hpp"

void auto_awp(){
    wing.set_value(true);

    chassis.setPose(0,0,180);


    //push alliance
    chassis.moveToPoint(0, -9, 1000,{.minSpeed = 100}); 
    firstStage.move(127);

    //go to match loader
    chassis.turnToPoint(0, -46, 1000);
    chassis.moveToPoint(0, 46, 3000,{.forwards = false });
    chassis.waitUntilDone();
    firstStage.move(0);

    //turn to match loader

    chassis.turnToHeading(90, 1000);
    

    //matchloader
    scraper.set_value(true);
    chassis.moveToPoint(12, 46, 1000);
    firstStage.move(127);
    pros::delay(1300);
    firstStage.move(0);


    //first goal
    chassis.turnToHeading(90, 1000);
    chassis.moveToPoint(-19.4, 47, 1500,{.forwards = false });
    chassis.waitUntilDone();
    
    leftMotors.move(-50);
    rightMotors.move(-50);
    intake.move(127);
    
    pros::delay(1700);
    chassis.setPose(-19.4, 46, 90);
    leftMotors.move(0);
    rightMotors.move(0);
    scraper.set_value(false);


    //6 blocks
    chassis.turnToPoint(-20, 32, 1000);
    chassis.waitUntilDone();
    intake.move(0);
    firstStage.move(127);
    chassis.moveToPoint(-35, 16, 1000,{.maxSpeed = 85, .minSpeed = 70, .earlyExitRange = 20});
    chassis.moveToPoint(-24, -31, 1500,{.maxSpeed = 85, .minSpeed = 70,});
    chassis.moveToPoint(-24.1, -31.1, 1000);
    chassis.waitUntilDone();
    

    //middle goal
    chassis.moveToPoint(-36.3, -13.5, 1000,{.forwards = false,.maxSpeed = 80});
    chassis.waitUntilDone();

    wing.set_value(false);
    firstStage.move(80);
    secondStage.move(50);
    pros::delay(750);
    wing.set_value(true);
    firstStage.move(0);
    secondStage.move(0);

    //second long goal
    chassis.moveToPoint(4, -48, 1500,{.minSpeed = 127});
    chassis.turnToHeading(90, 1000);
    firstStage.move(127);
    chassis.moveToPoint(-14.8, -49.6, 1000,{.forwards = false,.minSpeed = 127});
    chassis.waitUntilDone();
    secondStage.move(127);
    
    


}

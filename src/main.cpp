
#include "config.h"
#include "autos.hpp"
#include "dsr.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "main.h"



void initialize() {
    
    wing.set_value(true);
    pros::lcd::initialize(); 
    chassis.calibrate();
    chassis.setPose(0,0,180);


    pros::Task backgroundScreenTask([&]() {
        

        while (true) {
            
            pros::lcd::print(0, "X: %f", chassis.getPose().x); 
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); 
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); 

            pros::delay(50);
        }
    });
}


void disabled() {}


void competition_initialize() {}


void autonomous() {

    //auto_awp();

    //auto_left_7();

    //auto_right_7();

    //auto_left_counter();

    //auto_left_4();

    //auto_right_4();
   
    skills();

}





void opcontrol() {
    
    scraper.set_value(false);


    //variable declorations and initilizations
    bool wingOn = false;
    bool scraperOn = false;
    bool midOn = false;

    //motor break changing from brake to coast
    firstStage.set_brake_mode(pros::MotorBrake::coast);
    secondStage.set_brake_mode(pros::MotorBrake::coast);
    intake.set_brake_mode(pros::MotorBrake::coast);

    while (true) {

        // get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, rightX);

        //intake controlls
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ 
            firstStage.move(127);
            secondStage.move(-40);
            
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            intake.move(127);

        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ 
            intake.move(-127);

        }else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            firstStage.move(85);
            
        
        } else{
            firstStage.brake();
            secondStage.brake();
            intake.brake();
        }
        

        //wing controlls
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){ 
            wingOn = !wingOn;
            wing.set_value(wingOn);
        }

        //scraper pneumatic controlls
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
            scraperOn = !scraperOn;
            scraper.set_value(scraperOn);
        } 

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            midOn = !midOn;
            mid_goal.set_value(midOn);
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            pros::lcd::print(6, "front Ds %f", frontDistanceSensor.getDistance(WallAngles::FrontWallAngle));
            pros::lcd::print(7, "left Ds %f", leftDistanceSensor.getDistance(WallAngles::LeftWallAngle));

            ResetPose(frontDistanceSensor, WallAngles::FrontWallAngle, FeildWalls::FrontWall, false,
                      leftDistanceSensor, WallAngles::LeftWallAngle, FeildWalls::LeftWall, true);
        }



        pros::delay(10);
    }

}


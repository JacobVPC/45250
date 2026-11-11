
#include "config.h"
#include "autos.hpp"
#include "dsr.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "main.h"



void initialize() {
    
    pros::lcd::initialize(); 
    chassis.calibrate();
    chassis.setPose(0,0,0);


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

    chassis.setPose(0,0,0);
    chassis.turnToHeading(90, 10000,{.maxSpeed = 30,.minSpeed = 0});
    

}





void opcontrol() {
    
    


    //variable declorations and initilizations
    
    bool toggleOn = false;

    //motor break changing from brake to coast
    toggle.set_brake_mode(pros::MotorBrake::coast);
    cascade.set_brake_mode(pros::MotorBrake::brake);
    claw.set_brake_mode(pros::MotorBrake::brake);
   

    while (true) {

        // get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, -rightX);

        //motor controlls
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ 
            claw.move(127);
               
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            claw.move(-127);
        
        } else{
            claw.brake();
        }
        
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ 
            cascade.move(127);
               
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            cascade.move(-127);
        
        } else{
            cascade.brake();
        }
        
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
            toggleOn = !toggleOn;
        }

        toggle.move(toggleOn ? 127 : 0);

        // //wing controlls
        // if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){ 
        //     wingOn = !wingOn;
        //     wing.set_value(wingOn);
        // }

        // //scraper pneumatic controlls
        // if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        //     scraperOn = !scraperOn;
        //     scraper.set_value(scraperOn);
        // } 

        // if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        //     midOn = !midOn;
        //     mid_goal.set_value(midOn);
        // }



        pros::delay(10);
    }

}


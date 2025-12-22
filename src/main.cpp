#include "config.h"
#include "autos.hpp"
#include "main.h"


void initialize() {
    wing.set_value(true);
    pros::lcd::initialize(); 
    chassis.calibrate();


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

    //auto_left_mid();

    //auto_right_mid();

    //auto_right_elims();

    auto_left_elims();

    //skills();

}





void opcontrol() {

    scraper.set_value(false);


    //variable declorations and initilizations
    bool wingOn = false;
    bool scraperOn = false;

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
            secondStage.move(-25);
            
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            intake.move(127);

        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ 
            firstStage.move(-127);

        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ 
            intake.move(-127);

        }else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
            firstStage.move(110);

        } else{
            firstStage.brake();
            secondStage.brake();
            intake.brake();
        }
        

        //wing pneumatic controlls
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
            wingOn = !wingOn;
            wing.set_value(wingOn);

        } 

        //scraper pneumatic controlls
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
            scraperOn = !scraperOn;
            scraper.set_value(scraperOn);

        } 



        pros::delay(10);
    }

}


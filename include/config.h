#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include "pros/misc.h"




// With inlining: The compiler replaces every instance of 
// the function call with the function's code itself. This
//  eliminates the function call overhead, making the code run faster. 
// controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
inline pros::MotorGroup leftMotors({-13, -14, -15}, pros::MotorGearset::blue); 
inline pros::MotorGroup rightMotors({16, 17, 18}, pros::MotorGearset::blue);

//motors
inline pros::Motor firstStage(19, pros::MotorGearset::blue);
inline pros::Motor secondStage(-20,pros::MotorGearset::blue);
inline pros::MotorGroup intake({19,-20},pros::MotorGearset::blue);

// Inertial Sensor on port 10
inline pros::Imu imu(9);

// pneumatics
inline pros::adi::Pneumatics wing('b',LOW);
inline pros::adi::Pneumatics scraper('c',LOW);

// tracking wheels
inline pros::Rotation rotation_horizontal(-2);
inline pros::Rotation rotation_vertical(-1);

// tracking wheels
inline lemlib::TrackingWheel tw_vertical(&rotation_vertical, lemlib::Omniwheel::NEW_2, 0);

// drivetrain settings
inline lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.5, // 11.5 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 2.75" omnis
                              450, // drivetrain rpm is 600
                              8 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller PID
inline lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            35, // derivative gain (kD)
                                            0, // anti windup
                                            3, // small error range, in inches
                                            500, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            40 // maximum acceleration (slew)
);

// angular motion controller PID
inline lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             12.7, // derivative gain (kD)
                                             0, // anti windup
                                             3, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             6, // large error range, in degrees
                                             200, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
inline lemlib::OdomSensors sensors(&tw_vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            nullptr, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
inline lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
inline lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
inline lemlib::Chassis chassis(drivetrain,
                                 linearController,
                                 angularController,
                                 sensors,
                                 &throttleCurve,
                                 &steerCurve);

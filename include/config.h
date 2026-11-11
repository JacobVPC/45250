#ifndef CONFIG_H
#define CONFIG_H


#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motor_group.hpp"
#include "pros/misc.h"
#include "pros/optical.hpp"
#include "dsr.hpp"
#include "vector"

using namespace WallAngles;
using namespace HeadingOffsets;
using namespace FeildWalls;





// With inlining: The compiler replaces every instance of 
// the function call with the function's code itself. This
//  eliminates the function call overhead, making the code run faster. 

// controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
inline pros::MotorGroup leftMotors({12, 13}, pros::MotorGearset::blue); 
inline pros::MotorGroup rightMotors({-14, -15}, pros::MotorGearset::blue);
inline pros::MotorGroup AllMotors({12,13,-14,-15}, pros::MotorGearset::blue);
//motors
inline pros::Motor lcas(6,pros::MotorGearset::green);
inline pros::Motor rcas(-7,pros::MotorGearset::green);
inline pros::MotorGroup cascade({6,-7},pros::MotorGearset::green);
inline pros::Motor claw(-5); //5.5 w motor

inline pros::Motor ltoggle(-10,pros::MotorGearset::green);
inline pros::Motor rtoggle(9,pros::MotorGearset::green);
inline pros::MotorGroup toggle({-10,9},pros::MotorGearset::green);

// Inertial Sensor 
inline pros::Imu imu(17);



//group
inline std::vector<pros::adi::Pneumatics> psitoggle = {
    pros::adi::Pneumatics('a', LOW),
    pros::adi::Pneumatics('b', LOW)
};


// tracking wheels
inline pros::Rotation rotation_vertical(-16);



//distance sensors
inline pros::Distance frontDs(4);
inline pros::Distance leftDs(3);
inline pros::Distance rightDs(2);
inline pros::Distance backDs(1);

//distance sensor objects
// inline DistanceSensor frontDistanceSensor(frontDs, 4.95, 4.75, HeadingOffsets::HeadingOffsetFront);
// inline DistanceSensor leftDistanceSensor(leftDs, 5.25, 3, HeadingOffsets::HeadingOffsetLeft);
// inline DistanceSensor rightDistanceSensor(rightDs, 5.25, 3, HeadingOffsets::HeadingOffsetRight);


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
inline lemlib::ControllerSettings linearController(8, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            35, // derivative gain (kD)
                                            0, // anti windup
                                            0, // small error range, in inches
                                            0, // small error range timeout, in milliseconds
                                            0, // large error range, in inches
                                            0, // large error range timeout, in milliseconds
                                            0 // maximum acceleration (slew)
);

// angular motion controller PID
inline lemlib::ControllerSettings angularController(0.5, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             5, // derivative gain (kD)
                                             0, // anti windup
                                             1, // small error range, in degrees
                                             200, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
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



#endif // CONFIG_H
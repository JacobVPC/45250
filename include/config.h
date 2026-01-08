#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motor_group.hpp"
#include "pros/misc.h"
#include "pros/optical.hpp"






// With inlining: The compiler replaces every instance of 
// the function call with the function's code itself. This
//  eliminates the function call overhead, making the code run faster. 

// controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
inline pros::MotorGroup leftMotors({-13, -14, -15}, pros::MotorGearset::blue); 
inline pros::MotorGroup rightMotors({16, 17, 18}, pros::MotorGearset::blue);
inline pros::MotorGroup AllMotors({-13, -14, -15, 16, 17, 18}, pros::MotorGearset::blue);
//motors
inline pros::Motor firstStage(20, pros::MotorGearset::blue);
inline pros::Motor secondStage(-12,pros::MotorGearset::blue);
inline pros::MotorGroup intake({20,-12},pros::MotorGearset::blue);

// Inertial Sensor on port 10
inline pros::Imu imu(9);

// pneumatics
inline pros::adi::Pneumatics wing('b',LOW);
inline pros::adi::Pneumatics scraper('c',LOW);
inline pros::adi::Pneumatics mid_goal('a',LOW);

// tracking wheels
inline pros::Rotation rotation_vertical(19);

//optical sensors
inline pros::Optical top_optical(12);
inline pros::Optical middle_optical(11);

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
inline lemlib::ControllerSettings angularController(3, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             30, // derivative gain (kD)
                                             0, // anti windup
                                             0, // small error range, in degrees
                                             0, // small error range timeout, in milliseconds
                                             0, // large error range, in degrees
                                             0, // large error range timeout, in milliseconds
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


//distance sensors
inline pros::Distance frontDs(99);
inline pros::Distance leftDs(99);
inline pros::Distance rightDs(99);


namespace WallAngles {
    constexpr double BOTTOM = 0.0;    // horizontal wall at bottom
    constexpr double RIGHT = 90.0;    // vertical wall on right
    constexpr double TOP = 180.0;     // horizontal wall at top
    constexpr double LEFT = 270.0;    // vertical wall on left
}                                


namespace HeadingOffsets {
    constexpr double HOR = -90.0;    // right ds
    constexpr double HOF = 0.0;      // front ds
    constexpr double HOL = 90.0;      // left ds
}
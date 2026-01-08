#include "dsr.hpp"
#include "config.h"
#include <cmath>

double getDistance(
    pros::Distance &distanceSensor,
    double x_offset,
    double y_offset,
    double wall_angle,
    double heading_offset)
    {
        
    /* 

    heading offset for each ds 
    front = 0
    left = 90
    right = -90

    offsets for each sensor in inches

    front
    x =
    y = 

    left 
    x = 
    y =

    right
    x =
    y =

    */
    double distance_reading = distanceSensor.get_distance() / 25.4;

    double theta = (chassis.getPose().theta + heading_offset) - wall_angle;
    double thetaRad = theta * M_PI / 180;

    double sensor_component = cos(thetaRad) * distance_reading;
    double lateral_component = cos(thetaRad) * x_offset;
    double longitudinal_component = sin(thetaRad) * y_offset * -1;

    double distance = sensor_component + lateral_component + longitudinal_component;
    return distance;
    

}


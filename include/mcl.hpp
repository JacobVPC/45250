#pragma once
#include "lemlib/pose.hpp"
#include "pros/distance.hpp"
#include <vector>

struct Particle {                   // one possible robot pose
    double x;
    double y;
    double theta;
    double weight;
};

class mcl {

private:
// mcl steps
void predict(double dx, double dy, double dtheta);              //Applies robot motion to all particles


void updateWeights();


void resample();

// Helpers
double expectedDistance(double x, double y, double theta) ;


double gaussian(double mu, double sigma, double x);


void normalizeWeights();

// Sensors
pros::Distance& frontSensor;
pros::Distance& leftSensor;
pros::Distance& rightSensor;

// Particle set
std::vector<Particle> particles;

lemlib::Pose lastOdomPose;



public:

    mcl(                                //constructor
        pros::Distance& front,
        pros::Distance& left,
        pros::Distance& right
    );

    void initialize(double x, double y, double theta);      //create initial belief


    void update(const lemlib::Pose& odomPose);              //one full MCL iteration


    lemlib::Pose getPose() const;                                 // best estimated robot position

};
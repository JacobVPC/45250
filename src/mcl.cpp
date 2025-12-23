#include "mcl.hpp"
#include <cmath>   
#include <random>

//tune when i have robot
static constexpr int num_particles = 300;
static constexpr double motion_noise = 0.4;   // inches (how much uncertainty you add to movement).
static constexpr double turn_noise   = 0.02;  // radians (Adds noise to rotation)
static constexpr double sensor_noise = 1.5;   // inches (how much you trust your distance sensors)
static constexpr double feild_size = 144.0; // inches 




static std::default_random_engine ran;                  //random generator



static double randGaussian(double mean, double stddev) {        //random gaus
    std::normal_distribution<double> dist(mean, stddev);
    return dist(ran);
}


mcl::mcl(
    pros::Distance& front,
    pros::Distance& left,
    pros::Distance& right
) : frontSensor(front), leftSensor(left), rightSensor(right),
    lastOdomPose {0, 0, 0}  {
    
    ran.seed(pros::millis()); 
}
// constrct





void mcl::initialize(double startX, double startY, double startTheta) {
    particles.clear();

    for (int i = 0; i < num_particles; i++) {
        particles.push_back({
            startX + randGaussian(0, 1.0),
            startY + randGaussian(0, 1.0),
            startTheta + randGaussian(0, 0.05),
            1.0 / num_particles
        });
    }

    lastOdomPose = lemlib::Pose( //do not rly know what goin on here but there was error and this was solution
    static_cast<float>(startX),
    static_cast<float>(startY),
    static_cast<float>(startTheta)
);
}





void mcl::update(const lemlib::Pose& odomPose) {
    double dx = odomPose.x - lastOdomPose.x;
    double dy = odomPose.y - lastOdomPose.y;
    double dtheta = odomPose.theta - lastOdomPose.theta;

    lastOdomPose = odomPose;

    predict(dx, dy, dtheta);
    updateWeights();
    resample();
}





void mcl::predict(double dx, double dy, double dtheta) {
    for (auto& p : particles) {
        p.x     += dx + randGaussian(0, motion_noise);
        p.y     += dy + randGaussian(0, motion_noise);
        p.theta += dtheta + randGaussian(0, turn_noise);

         // Clamp to field boundaries
        p.x = std::clamp(p.x, 0.0, feild_size);
        p.y = std::clamp(p.y, 0.0, feild_size);
    }
}





void mcl::updateWeights() {
    int32_t front_raw = frontSensor.get();      //conv mm to in
    if (front_raw < 0 || front_raw > 2000) return; // Skip this update
    double front = front_raw / 25.4;


    int32_t left_raw = leftSensor.get();    
    if (left_raw < 0 || left_raw > 2000) return;
    double left = left_raw / 25.4;


    int32_t right_raw = rightSensor.get();    
    if (right_raw < 0 || right_raw > 2000) return;
    double right = right_raw / 25.4;





    for (auto& p : particles) {    //  Gaussian should compare expected vs actual
        double w = 1.0;

        double expected_front = expectedDistance(p.x, p.y, p.theta);
        double expected_left  = expectedDistance(p.x, p.y, p.theta + M_PI_2);
        double expected_right = expectedDistance(p.x, p.y, p.theta - M_PI_2);
   
        w *= gaussian(expected_front, sensor_noise, front);  // gaussian(expected, stddev, measured)
        w *= gaussian(expected_left, sensor_noise, left);
        w *= gaussian(expected_right, sensor_noise, right);
        p.weight = w;
    }

    normalizeWeights();
}





void mcl::normalizeWeights() {
    double sum = 0;
    for (auto& p : particles) sum += p.weight;

    if (sum == 0) return;

    for (auto& p : particles) p.weight /= sum;
}





void mcl::resample() {
    std::vector<double> weights;
    for (auto& p : particles) weights.push_back(p.weight);

    std::discrete_distribution<> dist(weights.begin(), weights.end());
    std::vector<Particle> newParticles;

    for (int i = 0; i < num_particles; i++) {
        Particle copy = particles[dist(ran)];             // Pick particle proportional to weight

        copy.x += randGaussian(0, 0.2);     // Add small noise to prevent all particles from being identical
        copy.y += randGaussian(0, 0.2);
        copy.theta += randGaussian(0, 0.01);


        copy.weight = 1.0 / num_particles;
        newParticles.push_back(copy);
    }

    particles = newParticles;
}




double mcl::expectedDistance(double x, double y, double theta) {
    double dx = cos(theta);
    double dy = sin(theta);

    double t = 1e9;

    if (dx > 0) t = std::min(t, (feild_size - x) / dx);
    if (dx < 0) t = std::min(t, -x / dx);
    if (dy > 0) t = std::min(t, (feild_size - y) / dy);
    if (dy < 0) t = std::min(t, -y / dy);

    return std::max(0.0, t);
}





double mcl::gaussian(double mean, double stddev, double x) {
    double coeff = 1.0 / (stddev * sqrt(2 * M_PI));
    return coeff * exp(-pow(x - mean, 2) / (2 * stddev * stddev));
}





lemlib::Pose mcl::getPose() const {
    double x = 0, y = 0, sinT = 0, cosT = 0;

    for (auto& p : particles) {
        x += p.x * p.weight;
        y += p.y * p.weight;
        sinT += sin(p.theta) * p.weight;
        cosT += cos(p.theta) * p.weight;
    }

    //Create pose using a valid constructor
    lemlib::Pose pose = lastOdomPose;

    //Overwrite fields
    pose.x = x;
    pose.y = y;
    pose.theta = atan2(sinT, cosT);

    return pose;
}



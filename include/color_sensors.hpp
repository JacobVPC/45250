#ifndef OPTICAL_DETECTION_HPP
#define OPTICAL_DETECTION_HPP
#include "pros/optical.hpp"


enum BlockColor {
    RED,
    BLUE,
    NONE
};

extern BlockColor detect_block_color(pros::Optical& optical_sensor, int min_proximity);

extern int count_blocks(pros::Optical& optical_sensor, int num_blocks, int timeout_ms, int delay);

#endif
#include "color_sensors.hpp"
#include "pros/llemu.hpp"
#include "config.h"



/**
 * Detects the color of a block using the optical sensor
 * 
 * @param optical_sensor The optical sensor object
 * @param min_proximity Minimum proximity value to consider (0-255, recommend 100-150)
 * @return BlockColor enum (RED, BLUE, or NONE)
 */
BlockColor detect_block_color(pros::Optical& optical_sensor, int min_proximity = 50) {
    double proximity = optical_sensor.get_proximity();
    if (proximity < min_proximity) { //make sure object is close
        return NONE;
    }
    
    // Get the hue value (0-360 degrees)
    double hue = optical_sensor.get_hue();
    
    // Red wraps around 0 degrees (350-360 and 0-10)
    if ((hue >= 350 && hue <= 360) || (hue >= 0 && hue <= 10)) {
        return RED;
    }
    // Blue is typically around 200-250 degrees
    else if (hue >= 200 && hue <= 250) {
        return BLUE;
    }
    
    return NONE;
}







int count_blocks(pros::Optical& optical_sensor, int num_blocks, int timeout_ms,  int delayMS){
    int blocks_scored = 0;              // Start at 0 blocks
    uint32_t start_time = pros::millis(); // Start the timer
    BlockColor last_color = NONE;
    

    while (blocks_scored < num_blocks) {

        if ((pros::millis() - start_time) > timeout_ms) { //timeout checker
            return blocks_scored; //returns early along w how many blocks scored
        }

        BlockColor detected = detect_block_color(optical_sensor);
        

        if ((detected == RED || detected == BLUE) && last_color == NONE) {
            blocks_scored++;  // Count it
        }
        pros::delay(delayMS); //delay in between for tuneing

        pros::lcd::print(9, "Progress: %d/%d", blocks_scored, num_blocks);


        pros::delay(20);
        last_color = detected;
    }
    return blocks_scored;
}
#include "autos.hpp"
#include "config.h"
#include "pros/rtos.hpp"

void auto_awp(){
    wing.set_value(true);

    chassis.setPose(0,0,180);

}
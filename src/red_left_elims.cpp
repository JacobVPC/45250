#include "autos.hpp"
#include "config.h"


ASSET(leftElims_txt);
void auto_left_elims(){

    chassis.setPose(0,0,0);

    firstStage.move(127);
    chassis.follow(leftElims_txt, 5, 3000);
}   
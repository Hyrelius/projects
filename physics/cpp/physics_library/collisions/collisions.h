#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "../integrators/state.h"

void floor_collision(State& state, long double floor_y, long double restitution = 1.0L);
    



#endif
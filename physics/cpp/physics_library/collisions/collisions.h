#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "../integrators/state.h"

void floor_collision(State& state, int floor_y, long double restitution = 1.0L);
void wall_collision(State& state, int wall, long double restitution);



#endif
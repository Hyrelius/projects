#include "../integrators/state.h"
#include <iostream>

void floor_collision(State& state, int floor_y, long double restitution /* = 1.0L */) {
    if (state.position[1] <= floor_y && state.velocity[1] < 0) {
        state.position[1] = floor_y;
        state.velocity[1] = -state.velocity[1] * restitution;
    }
}

void wall_collision(State& state, int wall, long double restitution) {
    if (wall > 0 && state.position[0] >= wall) {
        state.position[0] = wall;
        state.velocity[0] = -state.velocity[0] * restitution;


    }
    if (wall < 0 && state.position[0] <= wall) {
        state.position[0] = wall;
        state.velocity[0] = -state.velocity[0] * restitution;
    }
}
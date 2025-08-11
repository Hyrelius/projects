#include "../integrators/state.h"


void floor_collision(State& state, long double floor_y, long double restitution = 1.0L) {
    if (state.position[1] < floor_y) {
        state.position[1] = floor_y;
        state.velocity[1] = -state.velocity[1] * restitution;
    }
};
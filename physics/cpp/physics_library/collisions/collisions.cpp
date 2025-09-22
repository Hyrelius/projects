#include "../integrators/state.h"
#include <iostream>
#include <cmath>

void floor_collision(State &state, int floor_y, long double restitution /* = 1.0L */)
{
    if (state.position[1] <= floor_y && state.velocity[1] < 0)
    {
        state.position[1] = floor_y;
        state.velocity[1] = -state.velocity[1] * restitution;
    }
}

void wall_collision(State &state, int wall, long double restitution)
{
    if (wall > 0 && state.position[0] >= wall)
    {
        state.position[0] = wall;
        state.velocity[0] = -state.velocity[0] * restitution;
    }
    if (wall < 0 && state.position[0] <= wall)
    {
        state.position[0] = wall;
        state.velocity[0] = -state.velocity[0] * restitution;
    }
}

void collision(State &state1, State &state2, long double restitution /* = 1.0L */)
{
    // probably  useless but i have to do something
    //  masses
    long double m1 = state1.mass;
    long double m2 = state2.mass;
    // decomposed velcoty vectors
    // calculate collisions - learn equations
    // theser were not needed
    // m1v1 + m2v2 = m1u1 + m2u2
    // m1u1x + m2u2x = m1v1x + m2v2x
    // m2u1y + m2u2y = m1v1y + m2v2y
    // calculate line of centers
    std::vector<long double> line_of_centre = state2.position - state1.position;
    long double nx = line_of_centre[0];
    long double ny = line_of_centre[1];
    long double length = sqrt(nx * nx + ny * ny);
    if (length == 0)
        return;
    // normalize - but why?
    nx /= length;
    ny /= length;
    // what now
    //  update velcoties

    // add collision here lol
}

// how does it work planning
// ts requires mech which i dont know
//  time to self teach ig
// unrealistic physics ig?
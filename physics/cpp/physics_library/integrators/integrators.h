#ifndef INTEGRATORS
#define INTEGRATORS
#include "state.h"


State euler_step(State (*f)(State state, double), State state, double dt, double t);
State velocity_verlet_step();
State rk4_step();
#endif

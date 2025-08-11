#ifndef INTEGRATORS
#define INTEGRATORS
#include "state.h"


State euler_step(State (*f)(State state, long double), State state, long double dt, long double t);
State velocity_verlet_step();
State rk4_step();
#endif

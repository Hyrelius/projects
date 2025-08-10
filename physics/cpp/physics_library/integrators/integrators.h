#ifndef INTEGRATORS
#define INTEGRATORS
#include "state.h"


State euler_step();
State velocity_verlet_step();
State rk4_step();
#endif

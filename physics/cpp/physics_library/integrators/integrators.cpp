#include <iostream>
#include "integrators.h"
#include "state.h"



State euler_step(State (*f)(State state, double), State state, double dt, double t){ //
    State derivative = f(state, t);
    return {
        state.position + (dt * derivative.position),
        state.velocity + (dt * derivative.velocity)
        //yes i am aware of this terrible, tragic code error but it is late and i cba and im off to play abf
    };
};

State velocity_verlet_step(){

};

State rk4_step(){

};
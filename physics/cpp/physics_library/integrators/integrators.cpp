#include <iostream>
#include "integrators.h"
#include "state.h"



State euler_step(State (*f)(State state, long double), State state, long double dt, long double t){ //
    State derivative = f(state, t);
    return {
        add_vectors(state.position, multiply_vector(derivative.position, dt)),
        add_vectors(state.velocity, multiply_vector(derivative.velocity, dt))
        //yes i am aware of this terrible, tragic code error but it is late and i cba and im off to play abf
    };
};

State velocity_verlet_step(State (*f)(State state, long double), State state, long double dt, long double t) {
    std::vector<long double> acceleration = f(state, t).velocity; 
    state.position = add_vectors(add_vectors(state.position, multiply_vector(state.velocity, dt)), multiply_vector(multiply_vector(acceleration, dt*dt), 0.5 ));
    std::vector<long double> new_acceleration = f(state, t + dt).velocity;
    state.velocity = add_vectors(state.velocity, multiply_vector((multiply_vector(add_vectors(acceleration, new_acceleration), 0.5)), dt));
};  
//holy moly that was a mess


State rk4_step(){

};

//comment
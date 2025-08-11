#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "physics_library/integrators/integrators.h"
#include "physics_library/integrators/state.h"
#include "physics_library/collisions/collisions.h"

class Ball {
    public:
        //properties
        State state;
        int mass = 1;
        int radius = 1;

        //methods
        std::vector<long double> getPosition() const {
            return state.position;
        }

        std::vector<long double> getVelocity() const {
            return state.velocity;
        }

        
};


State differential_equation(State state, long double /*t*/) {
    state.position = state.velocity;
    state.velocity[0] = 0;
    state.velocity[1] = -9.81L; 
    return state;
}


int main() {
    int steps = 100;

    State initial_state;
    initial_state.position = {0.0L, 0.0L};
    initial_state.velocity = {0.0L, 10.0L};

    Ball ball;
    ball.state = initial_state;

    std::vector<long double> state_positions(steps);
    for (int i = 0; i < steps; i++) {
        state_positions[i] = ball.getPosition()[1];
        ball.state = rk4_step(differential_equation, ball.state, 0.1L, i * 0.1L);
        floor_collision(ball.state, 0.9L);
    }

    std::cout << "Ball positions after RK4 steps:\n";
    for (int i = 0; i < steps; i++) {
        std::cout << "Step " << i << ": Position = " << state_positions[i] << "\n";
    };



}
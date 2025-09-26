#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "physics_library/integrators/integrators.h"
#include "physics_library/integrators/state.h"
#include "physics_library/collisions/collisions.h"

class Ball
{
public:
    // properties
    State state;
    long double mass = 1.0L;
    int radius = 1;

    // methods
    std::vector<long double> getPosition() const
    {
        return state.position;
    }

    std::vector<long double> getVelocity() const
    {
        return state.velocity;
    }

    std::vector<long double> getMomentum() const
    {
        return mass * state.velocity;
    }
};

// csv export function is ai
void export_to_csv(const std::vector<long double> &data, const std::vector<long double> &times, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << "time,value\n";
        for (size_t i = 0; i < data.size() && i < times.size(); ++i)
        {
            file << std::fixed << std::setprecision(6) << times[i] << "," << data[i] << "\n";
        }
        file.close();
    }
    else
    {
        std::cerr << "Error opening file: " << filename << "\n";
    }
}

State differential_equation(State derivative, long double /*t*/)
{
    derivative.position = derivative.velocity;
    derivative.velocity[0] = 0.0L;
    derivative.velocity[1] = 0.0L;
    return derivative;
}

int main()
{

    int steps = 10000;
    State initial_state = {{0.0L, 0.0L}, {2.0L, 0.0L}};

    Ball ball;
    ball.state = initial_state;

    std::vector<long double> state_positions(steps);
    std::vector<long double> state_momentum(steps);
    long double dt = 0.1L;
    std::vector<long double> times(steps);

    for (int i = 0; i < steps; i++)
    {
        state_positions[i] = ball.getPosition()[0];
        state_momentum[i] = ball.getMomentum()[0];
        ball.state = rk4_step(differential_equation, ball.state, 0.1L, i * 0.1L);
        floor_collision(ball.state, 0, 0.8L);
        wall_collision(ball.state, 5, 0.5L);
        wall_collision(ball.state, -5, 0.5L);
        times[i] = i * dt;
    }

    for (int i = 0; i < steps; i++)
    {
        std::cout << "Step " << i << ": Position = " << state_positions[i] << ": Momentum = " << state_momentum[i] << "\n";
    };

    export_to_csv(state_positions, times, "ball_positions.csv");
    return 0;
}
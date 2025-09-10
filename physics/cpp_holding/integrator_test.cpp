#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "physics_library/integrators/integrators.h"
#include "physics_library/integrators/state.h"
// slowly less ai

// Constants
const long double PI = std::acos(-1.0L);
const long double omega = 2 * PI;  // angular frequency (1 Hz)
const long double A = 1.0L;        // initial displacement
const long double v0 = 0.0L;       // initial velocity
const long double t_max = 1000.0L; // time duration
const long double dt = 0.001L;     // timestep

// Differential equation: dx/dt = v, dv/dt = -omega^2 * x
State differential_equation(State state, long double /*t*/)
{
    State result;
    result.position = state.velocity;
    result.velocity.resize(state.position.size());
    for (size_t i = 0; i < state.position.size(); ++i)
        result.velocity[i] = -omega * omega * state.position[i];
    return result;
}

// Analytical solution for 1D oscillator
long double analytical_solution(long double t)
{
    return A * std::cos(omega * t) + (v0 / omega) * std::sin(omega * t);
}

std::vector<long double> run_simulation(
    State (*step_func)(State (*)(State, long double), State, long double, long double),
    State initial_state,
    const std::vector<long double> &t_array)
{
    std::vector<long double> positions;
    State s = initial_state;
    for (long double t_i : t_array)
    {
        positions.push_back(s.position[0]);
        s = step_func(differential_equation, s, dt, t_i);
    }
    return positions;
}

// Error calculation
void calculate_errors(const std::vector<long double> &numerical, const std::vector<long double> &analytical,
                      std::vector<long double> &error, long double &rmse, long double &max_error)
{
    long double sum_sq = 0.0L;
    max_error = 0.0L;
    error.resize(numerical.size());
    for (size_t i = 0; i < numerical.size(); ++i)
    {
        error[i] = numerical[i] - analytical[i];
        sum_sq += error[i] * error[i];
        if (std::abs(error[i]) > max_error)
            max_error = std::abs(error[i]);
    }
    rmse = std::sqrt(sum_sq / static_cast<long double>(numerical.size()));
}

int main()
{
    using clock = std::chrono::high_resolution_clock;
    auto start_time = clock::now(); // Start timer

    // Time array
    std::vector<long double> t;
    for (long double ti = 0.0L; ti < t_max; ti += dt)
        t.push_back(ti);

    State initial_state = {{A}, {v0}};

    // Analytical solution
    std::vector<long double> x_analytical(t.size());
    for (size_t i = 0; i < t.size(); ++i)
        x_analytical[i] = analytical_solution(t[i]);

    // Run simulations
    std::vector<long double> x_rk4 = run_simulation(rk4_step, initial_state, t);
    std::vector<long double> x_euler = run_simulation(euler_step, initial_state, t);
    std::vector<long double> x_verlet = run_simulation(velocity_verlet_step, initial_state, t);

    // Error calculation and print stats
    struct MethodResult
    {
        std::string name;
        std::vector<long double> values;
    };
    std::vector<MethodResult> methods = {
        {"RK4", x_rk4},
        {"Euler", x_euler},
        {"Velocity Verlet", x_verlet}};

    for (const auto &method : methods)
    {
        std::vector<long double> error;
        long double rmse, max_error;
        calculate_errors(method.values, x_analytical, error, rmse, max_error);
        std::cout << method.name << ":\n  RMSE: " << std::setprecision(6) << std::scientific << static_cast<double>(rmse)
                  << "\n  Max Error: " << std::setprecision(6) << std::scientific << static_cast<double>(max_error) << "\n\n";
    }

    auto end_time = clock::now(); // End timer
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Execution time: " << elapsed.count() << " seconds\n";

    return 0;
}

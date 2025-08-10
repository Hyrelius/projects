#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
//still ai 
//still learning cpp

const long double PI = std::acos(-1.0L);

// Simple harmonic oscillator parameters
const long double omega = 2 * PI; // angular frequency (1 Hz)
const long double A = 1.0L;       // initial displacement
const long double v0 = 0.0L;      // initial velocity
const long double t_max = 100.0L; // time duration
const long double dt = 0.001L;    // timestep

struct State {
    long double x;
    long double v;
};

// Differential equation: dx/dt = v, dv/dt = -omega^2 * x
State differential_equation(const State& state, long double /*t*/) {
    return { state.v, -omega * omega * state.x };
}

// Euler integrator
State euler_step(State (*f)(const State&, long double), const State& state, long double dt, long double t) {
    State deriv = f(state, t);
    return { state.x + dt * deriv.x, state.v + dt * deriv.v };
}

// RK4 integrator
State rk4_step(State (*f)(const State&, long double), const State& state, long double dt, long double t) {
    State k1 = f(state, t);
    State k2 = f({ state.x + 0.5L * dt * k1.x, state.v + 0.5L * dt * k1.v }, t + 0.5L * dt);
    State k3 = f({ state.x + 0.5L * dt * k2.x, state.v + 0.5L * dt * k2.v }, t + 0.5L * dt);
    State k4 = f({ state.x + dt * k3.x, state.v + dt * k3.v }, t + dt);

    return {
        state.x + (dt / 6.0L) * (k1.x + 2.0L * k2.x + 2.0L * k3.x + k4.x),
        state.v + (dt / 6.0L) * (k1.v + 2.0L * k2.v + 2.0L * k3.v + k4.v)
    };
}

// Velocity Verlet integrator
State velocity_verlet_step(State (*f)(const State&, long double), const State& state, long double dt, long double t) {
    long double a = f(state, t).v;
    long double x_new = state.x + state.v * dt + 0.5L * a * dt * dt;
    State temp = { x_new, state.v };
    long double a_new = f(temp, t + dt).v;
    long double v_new = state.v + 0.5L * (a + a_new) * dt;
    return { x_new, v_new };
}

// Analytical solution
long double analytical_solution(long double t) {
    return A * std::cos(omega * t) + (v0 / omega) * std::sin(omega * t);
}

// Simulation runner
std::vector<long double> run_simulation(State (*step_func)(State (*)(const State&, long double), const State&, long double, long double), State initial_state, const std::vector<long double>& t_array) {
    std::vector<long double> positions;
    State s = initial_state;
    for (long double t_i : t_array) {
        positions.push_back(s.x);
        s = step_func(differential_equation, s, dt, t_i);
    }
    return positions;
}

// Error calculation
void calculate_errors(const std::vector<long double>& numerical, const std::vector<long double>& analytical,
                     std::vector<long double>& error, long double& rmse, long double& max_error) {
    long double sum_sq = 0.0L;
    max_error = 0.0L;
    error.resize(numerical.size());
    for (size_t i = 0; i < numerical.size(); ++i) {
        error[i] = numerical[i] - analytical[i];
        sum_sq += error[i] * error[i];
        if (std::abs(error[i]) > max_error) max_error = std::abs(error[i]);
    }
    rmse = std::sqrt(sum_sq / static_cast<long double>(numerical.size()));
}

int main() {
    using clock = std::chrono::high_resolution_clock;
    auto start_time = clock::now();  // Start timer

    // Time array
    std::vector<long double> t;
    for (long double ti = 0.0L; ti < t_max; ti += dt)
        t.push_back(ti);

    State initial_state = { A, v0 };

    // Analytical solution
    std::vector<long double> x_analytical(t.size());
    for (size_t i = 0; i < t.size(); ++i)
        x_analytical[i] = analytical_solution(t[i]);

    // Run simulations
    std::vector<long double> x_rk4 = run_simulation(rk4_step, initial_state, t);
    std::vector<long double> x_euler = run_simulation(euler_step, initial_state, t);
    std::vector<long double> x_verlet = run_simulation(velocity_verlet_step, initial_state, t);

    // Error calculation and print stats
    struct MethodResult {
        std::string name;
        std::vector<long double> values;
    };
    std::vector<MethodResult> methods = {
        { "RK4", x_rk4 },
        { "Euler", x_euler },
        { "Velocity Verlet", x_verlet }
    };

    for (const auto& method : methods) {
        std::vector<long double> error;
        long double rmse, max_error;
        calculate_errors(method.values, x_analytical, error, rmse, max_error);
        std::cout << method.name << ":\n  RMSE: " << std::setprecision(6) << std::scientific << static_cast<double>(rmse)
                  << "\n  Max Error: " << std::setprecision(6) << std::scientific << static_cast<double>(max_error) << "\n\n";
    }

    auto end_time = clock::now();  // End timer
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Execution time: " << elapsed.count() << " seconds\n";

    return 0;
}

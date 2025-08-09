#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
//                                                                                                 what do each of these do?
const double PI = std::acos(-1.0); // Define M_PI if not already defined

// Simple harmonic oscillator parameters
const double omega = 2 * PI; // angular frequency (1 Hz)
const double A = 1.0;          // initial displacement
const double v0 = 0.0;         // initial velocity
const double t_max = 100.0;    // time duration
const double dt = 0.001;       // timestep

struct State {
    double x;
    double v;
};
//                                                                                                  is an object faster than an array?
// Differential equation: dx/dt = v, dv/dt = -omega^2 * x
State differential_equation(const State& state, double /*t*/) {
    return { state.v, -omega * omega * state.x };
}
//                                                                                                  so does the State before a function mean that it returns a State object?
// Euler integrator
State euler_step(State (*f)(const State&, double), const State& state, double dt, double t) {
    State deriv = f(state, t);
    return { state.x + dt * deriv.x, state.v + dt * deriv.v };
}
//                                                                                                  Why the (*f)(foo) syntax, why use a pointer/how does a pointer work here, why the &?
// RK4 integrator
State rk4_step(State (*f)(const State&, double), const State& state, double dt, double t) {
    State k1 = f(state, t);
    State k2 = f({ state.x + 0.5 * dt * k1.x, state.v + 0.5 * dt * k1.v }, t + 0.5 * dt);
    State k3 = f({ state.x + 0.5 * dt * k2.x, state.v + 0.5 * dt * k2.v }, t + 0.5 * dt);
    State k4 = f({ state.x + dt * k3.x, state.v + dt * k3.v }, t + dt);

    return {
        state.x + (dt / 6.0) * (k1.x + 2 * k2.x + 2 * k3.x + k4.x),
        state.v + (dt / 6.0) * (k1.v + 2 * k2.v + 2 * k3.v + k4.v)
    };
}
//                                                                                                    returns an array {state.x, state.y} or the State object?
// Velocity Verlet integrator
State velocity_verlet_step(State (*f)(const State&, double), const State& state, double dt, double t) {
    double a = f(state, t).v;
    double x_new = state.x + state.v * dt + 0.5 * a * dt * dt;
    State temp = { x_new, state.v };
    double a_new = f(temp, t + dt).v;
    double v_new = state.v + 0.5 * (a + a_new) * dt;
    return { x_new, v_new };
}

// Analytical solution
double analytical_solution(double t) {
    return A * std::cos(omega * t) + (v0 / omega) * std::sin(omega * t);
}

// Simulation runner
std::vector<double> run_simulation(State (*step_func)(State (*)(const State&, double), const State&, double, double),        //again what da pointer do
                                  State initial_state, const std::vector<double>& t_array) {
    std::vector<double> positions;
    State s = initial_state;
    for (double t_i : t_array) {
        positions.push_back(s.x);
        s = step_func(differential_equation, s, dt, t_i);
    }
    return positions;
}
//                                                                                                                          describe the strucutre and syntax of std::vector
//                                                            j                                                              what does .push_back() do?
// Error calculation
void calculate_errors(const std::vector<double>& numerical, const std::vector<double>& analytical,
                     std::vector<double>& error, double& rmse, double& max_error) {
    double sum_sq = 0.0;
    max_error = 0.0;
    error.resize(numerical.size());
    for (size_t i = 0; i < numerical.size(); ++i) {
        error[i] = numerical[i] - analytical[i];
        sum_sq += error[i] * error[i];
        if (std::abs(error[i]) > max_error) max_error = std::abs(error[i]);
    }
    rmse = std::sqrt(sum_sq / numerical.size());
}

int main() {
    using clock = std::chrono::high_resolution_clock;
    auto start_time = clock::now();  // Start timer

    // Time array
    std::vector<double> t;
    for (double ti = 0.0; ti < t_max; ti += dt)
        t.push_back(ti);

    State initial_state = { A, v0 };

    // Analytical solution
    std::vector<double> x_analytical(t.size());
    for (size_t i = 0; i < t.size(); ++i)
        x_analytical[i] = analytical_solution(t[i]);

    // Run simulations
    std::vector<double> x_rk4 = run_simulation(rk4_step, initial_state, t);
    std::vector<double> x_euler = run_simulation(euler_step, initial_state, t);
    std::vector<double> x_verlet = run_simulation(velocity_verlet_step, initial_state, t);

    // Error calculation and print stats
    struct MethodResult {
        std::string name;
        std::vector<double> values;
    };
    std::vector<MethodResult> methods = {
        { "RK4", x_rk4 },
        { "Euler", x_euler },
        { "Velocity Verlet", x_verlet }
    };

    for (const auto& method : methods) {
        std::vector<double> error;
        double rmse, max_error;
        calculate_errors(method.values, x_analytical, error, rmse, max_error);
        std::cout << method.name << ":\n  RMSE: " << std::setprecision(6) << std::scientific << rmse
                  << "\n  Max Error: " << std::setprecision(6) << std::scientific << max_error << "\n\n";
    }

    auto end_time = clock::now();  // End timer
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Execution time: " << elapsed.count() << " seconds\n";

    return 0;
}

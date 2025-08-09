from physlibrary.integrators import rk4, velocity_verlet, euler
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
import datetime as dte
#simple harmonic oscillator test

#parameters
omega = 2 * np.pi         # angular frequency (1 Hz)
A = 1.0                   # initial displacement
v0 = 0.0                  # initial velocity
B = v0 / omega
t_max = 100               # time duration
dt = 0.001                # timestep
t = np.arange(0, t_max, dt)

initial_state = np.array([A, v0])

#diffrentual equation
def diffrential_equation(state, t):
    x, v = state
    dxdt = v
    dvdt = -omega**2 * x
    return np.array([dxdt, dvdt])

def shm_equation_scipy(t, state):
    x, v = state  # state is a numpy array like [x, v]
    dxdt = v
    dvdt = -omega**2 * x
    return [dxdt, dvdt]


#simulation
def run_simulation(step_func, state, t_array):
    states = []
    s = state.copy()
    for t_i in t_array:
        states.append(s[0])  # store position
        s = step_func(diffrential_equation, s, dt, t_i)
    return np.array(states)

simtime = dte.datetime.now()
#run simulations
x_analytical = A * np.cos(omega * t) + (v0 / omega) * np.sin(omega * t) # analytical solution as the "correct" answer
x_rk4 = run_simulation(rk4.rk4_step, initial_state.copy(), t)
x_euler = run_simulation(euler.euler_step, initial_state.copy(), t)
x_verlet = run_simulation(velocity_verlet.velocity_verlet_step, initial_state.copy(), t)
sol = solve_ivp(shm_equation_scipy, [0, t_max], initial_state, t_eval=t, method='RK45', rtol=1e-10, atol=1e-12)
x_scipy = sol.y[0]

#eoorr calculation
def calculate_errors(numerical, analytical):
    error = numerical - analytical
    rmse = np.sqrt(np.mean(error**2))
    max_error = np.max(np.abs(error))
    return error, rmse, max_error

methods = {
    "RK4": x_rk4,
    "Scipy RK45": x_scipy,
    "Euler": x_euler,
    "Velocity Verlet": x_verlet
}





#below with ai because still leaning matplotlib
# --- Print error stats ---
for name, x_num in methods.items():
    error, rmse, max_err = calculate_errors(x_num, x_analytical)
    print(f"{name}:\n  RMSE: {rmse:.6e}\n  Max Error: {max_err:.6e}\n")



simtime = dte.datetime.now() - simtime
print(f"Simulation time: {simtime.total_seconds()} seconds")


plt.figure(figsize=(14, 6))
# Plotting the results
plt.subplot(1, 2, 1)
plt.plot(t, x_analytical, 'k--', label="Analytical", linewidth=1)
for name, x_num in methods.items():
    plt.plot(t, x_num, label=name)
plt.xlabel("Time (s)")
plt.ylabel("Displacement")
plt.title("SHM: Analytical vs Numerical Methods")
plt.legend()
plt.grid(True)

# Error plot
plt.subplot(1, 2, 2)
for name, x_num in methods.items():
    plt.plot(t, x_num - x_analytical, label=f"{name} Error")
plt.xlabel("Time (s)")
plt.ylabel("Error")
plt.title("Deviation from Analytical Solution")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
import numpy as np
import matplotlib.pyplot as plt

#constants
g = 9.81

#pendulum variables
L1 = 1.0
L2 = 1.0
m1 = 1.0
m2 = 1.0

#initial conditions
theta1 = np.pi/2
theta2 = np.pi/2
w1 = 0
w2 = 0

#time step
dt = 0.001
T = 60
steps = int(T/dt)

"""
theta1'= w1
theta2' = w2
and w' could be seen as theta''
but we have used newtonian notation for clarity and readability

change variables above for different conditions
animtion coming soon^tm???
"""
"""
velocity verlet (taken from https://www.algorithm-archive.org/contents/verlet_integration/verlet_integration.html)
x(t+dt) = x(t) + v(t)dt + 1/2a(t)dt^2
v(t+dt) = v(t) + 1/2(a(t) + a(t+dt))dt
"""

def calculate_acceleration(theta1, theta2, w1, w2, L1, L2, m1, m2):
    delta = theta2 - theta1
    w1_dot = (m2 * L1 * w1**2 * np.sin(delta) * np.cos(delta) + m2 * g * np.sin(theta2) * np.cos(delta) + m2 * L2 * w2**2 *np.sin(delta) -(m1 + m2) * g * np.sin(theta1)) / ((m1 + m2) * L1 - m2 * L1 * np.cos(delta)**2)
    w2_dot = (-m2 * L2  * w2**2 * np.sin(delta) * np.cos(delta) + (m1 + m2) * (g * np.sin(theta1) * np.cos(delta) - L1 * w1**2 * np.sin(delta) - g * np.sin(theta2))) / ((L2/L1) * ((m1 + m2) * L1 - m2 * L1 * np.cos(delta)**2))
    return w1_dot, w2_dot


def calculate_lagrangian():
    #take in variables needed
    pass

#inputs intial conditions and outputs array for said conditions
def velocity_verlet(theta1, theta2, w1, w2, L1, L2, m1, m2):

    theta1_array = np.zeros([steps])
    theta2_array = np.zeros([steps])
    w1_array = np.zeros([steps])
    w2_array = np.zeros([steps])
    lagrangian = np.zeros([steps])
    kinetic = np.zeros([steps])
    potential = np.zeros([steps])
    #loop to loop over each step and add results to arrays
    for i in range(steps):
        w1_dot, w2_dot = calculate_acceleration(theta1, theta2, w1, w2, L1, L2, m1, m2)
        #calculate new angles given our current velocity and acceleration
        theta1_new = theta1 + w1 * dt + 0.5 * w1_dot * dt**2
        theta2_new = theta2 + w2 * dt + 0.5 * w2_dot * dt**2

        theta1_array[i] = theta1_new
        theta2_array[i] = theta2_new

        #calculate new acceleration at new angles
        w1_dot_new, w2_dot_new = calculate_acceleration(theta1_new, theta2_new, w1, w2, L1, L2, m1, m2)

        #calculate new velocities with new acceleration
        w1_new = w1 + 0.5 * (w1_dot + w1_dot_new) * dt
        w2_new = w2 + 0.5 * (w2_dot + w2_dot_new) * dt

        w1_array[i] = w1_new
        w2_array[i] = w2_new

        #add calculations for lagrangian etc
        

        #update variables for next loop
        theta1 = theta1_new
        theta2 = theta2_new
        w1 = w1_new
        w2 = w2_new

    #self explanatory
    return theta1_array, theta2_array, w1_array, w2_array

#copius comments because i am dumb

def cartesian_coordinates(theta1, theta2, L1, L2):
    x1 = L1 * np.sin(theta1)
    y1 = -L1 * np.cos(theta1)
    x2 = x1 + L2 * np.sin(theta2)
    y2 = y1 - L2 * np.cos(theta2)
    return x1, y1, x2, y2



theta1_array, theta2_array, w1_array, w2_array = velocity_verlet(theta1, theta2, w1, w2, L1, L2, m1, m2)
time_array = np.arange(0, T, dt)

#plot angles against time
plt.plot(time_array, theta1_array)
plt.plot(time_array, theta2_array)
plt.show()


#============================
# Animation of the double pendulum
from matplotlib.animation import FuncAnimation

# Calculate (x, y) positions for both bobs over time
x1, y1, x2, y2 = cartesian_coordinates(theta1_array, theta2_array, L1, L2)

fig, ax = plt.subplots(figsize=(6, 6))
ax.set_xlim(-L1-L2-0.2, L1+L2+0.2)
ax.set_ylim(-L1-L2-0.2, L1+L2+0.2)
ax.set_aspect('equal')
ax.grid()

line, = ax.plot([], [], 'o-', lw=2)
trace, = ax.plot([], [], '-', lw=1, alpha=0.5)

# For tracing the path of the second bob
trace_x, trace_y = [], []

# Initialization function
def init():
    line.set_data([], [])
    trace.set_data([], [])
    return line, trace

# Animation function
def update(frame):
    thisx = [0, x1[frame], x2[frame]]
    thisy = [0, y1[frame], y2[frame]]
    line.set_data(thisx, thisy)
    trace_x.append(x2[frame])
    trace_y.append(y2[frame])
    trace.set_data(trace_x, trace_y)
    return line, trace

ani = FuncAnimation(fig, update, frames=range(0, steps, 10), init_func=init, blit=True, interval=10)
plt.title('Double Pendulum Animation')
plt.show()

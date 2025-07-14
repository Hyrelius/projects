import numpy as np

#constants
g = 9.81
L1 = 1.0
L2 = 1.0
m1 = 1.0
m2 = 1.0

#initial conditions
theta1 = np.pi/4
theta2 = np.pi/4
w1 = 0
w2 = 0

#time step
dt = 0.01
T = 10.0
steps = int(T/dt)

#initialise blank arrays
theta1_array = np.zeros([steps])
theta2_array = np.zeros([steps])
w1_array = np.zeros([steps])
w2_array = np.zeros([steps])

def calculate_acceleration(theta1, theta2, w1, w2):
    delta = theta2 - theta1
    w1_dot = (m2*L1*(w1**2)*np.sin(delta)*np.cos(delta) + m2*g*np.sin(theta2)*np.cos(delta) + m2*L2*(w2**2)*np.sin(delta))/(L1*(m1 + m2*(1 - np.cos(delta)**2)))
    w2_dot = (-m2*L2*(w2**2)*np.sin(delta)*np.cos(delta) + (m1 + m2)*g*np.sin(theta1) - m2*L1*(w1**2)*np.sin(delta))/(L2*(m1 + m2*(1 - np.cos(delta)**2)))
    return w1_dot, w2_dot

#loop structure
#velocity verlet
#appends to an array
#repeated for each step


def velocity_verlet(theta1, theta2, w1, w2):
    #calculate acceleration
    #
    pass
import numpy as np

#constants
g = 9.81

#pendulum variables
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
dt = 0.001
T = 10.0
steps = int(T/dt)

"""
theta1'= w1
theta2' = w2
and w' could be seen as theta''
but we have used newtonian notation for clarity and readability

change variables above for different conditions
animtion coming soon^tm???
"""


def calculate_acceleration(theta1, theta2, w1, w2, L1, L2, m1, m2):
    delta = theta2 - theta1
    w1_dot = (m2*L1*(w1**2)*np.sin(delta)*np.cos(delta) + m2*g*np.sin(theta2)*np.cos(delta) + m2*L2*(w2**2)*np.sin(delta))/(L1*(m1 + m2*(1 - np.cos(delta)**2)))
    w2_dot = (-m2*L2*(w2**2)*np.sin(delta)*np.cos(delta) + (m1 + m2)*g*np.sin(theta1) - m2*L1*(w1**2)*np.sin(delta))/(L2*(m1 + m2*(1 - np.cos(delta)**2)))
    return w1_dot, w2_dot

#inputs intial conditions and outputs array for said conditions
def velocity_verlet(theta1, theta2, w1, w2, L1, L2, m1, m2):

    theta1_array = np.zeros([steps])
    theta2_array = np.zeros([steps])
    w1_array = np.zeros([steps])
    w2_array = np.zeros([steps])

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

import numpy as np

#constants
g = 9.81
L1 = 1.0
L2 = 1.0
m1 = 1.0
m2 = 1.0

#equations of motion
delta = theta2 - theta1
theta1_dot = w1
theta2_dot = w2
w1_dot = (m2*L1*(w1**2)*np.sin(delta)*np.cos(delta) + m2*g*np.sin(theta2)*np.cos(delta) + m2*L2*(w2**2)*np.sin(delta))/(L1*(m1 + m2*(1 - np.cos(delta)**2)))
w2_dot = (-m2*L2*(w2**2)*np.sin(delta)*np.cos(delta) + (m1 + m2)*g*np.sin(theta1) - m2*L1*(w1**2)*np.sin(delta))/(L2*(m1 + m2*(1 - np.cos(delta)**2)))


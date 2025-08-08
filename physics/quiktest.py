#each ball contains its state, which is an array of its positions and velocities
from physlibrary.integrators.rk4 import *
from physlibrary.diffrential_equations import basic
import numpy as np
import matplotlib.pyplot as plt
class ball:
    def __innit__(self, state):
        self.state = state

    def get_position(self):
        n = int(len(self.state) / 2)
        return self.state[:n] 

    def get_velocity(self):
        n = int(len(self.state) / 2)
        return self.state[n:] 


steps = 22
state = [0,0,0,10]
baller = ball()
baller.state = state
positions = np.zeros(steps)
for i in range(steps):
    positions[i] = baller.get_position()[1]
    baller.state = rk4_step(basic, baller.state, 0.1, i * 0.1)

print(positions)
plt.plot(np.arange(steps) * 0.1, positions)
plt.xlabel('Time (s)')  
plt.ylabel('Vertical Position (m)')
plt.title('Vertical Position of Ball Over Time')    
plt.grid()
plt.show()
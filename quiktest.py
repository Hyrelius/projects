#each ball contains its state, which is an array of its positions and velocities
#import sys
#import os
#import numpy as np 

#sys.path.append(os.path.join(os.path.dirname(__file__), 'physiks_library'))

from physiks_library.rk4 import *

class ball:
    def __innit__(self, state):
        self.state = state

    def get_position(self):
        n = int(len(self.state) / 2)
        return self.state[:n] 

    def get_velocity(self):
        n = int(len(self.state) / 2)
        return self.state[n:] 

rk4_step()
state = [1,2,5,6]
baller = ball()
baller.state = state
print(baller.get_position())

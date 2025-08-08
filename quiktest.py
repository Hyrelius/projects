#each ball contains its state, which is an array of its positions and velocities
from physiks_library.rk4 import *
from physiks_library.diffrential_equations import basic


class ball:
    def __innit__(self, state):
        self.state = state

    def get_position(self):
        n = int(len(self.state) / 2)
        return self.state[:n] 

    def get_velocity(self):
        n = int(len(self.state) / 2)
        return self.state[n:] 
state = [1,2,5,6]
baller = ball()
baller.state = state
baller.state = rk4_step(basic, state, 0.1, 0)


print(baller.get_position())

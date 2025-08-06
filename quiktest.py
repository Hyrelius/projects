#each ball contains its state, which is an array of its positions and velocities
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
print(baller.get_position())

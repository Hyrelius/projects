class ball:
    def __init__(self, mass, position, velocity):
        self.mass = mass
        self.position = position
        self.velocity = velocity

    def update(self, dt):
        self.position += self.velocity * dt

    def get_position(self):
        return self.position

    def get_velocity(self):
        return self.velocity
    
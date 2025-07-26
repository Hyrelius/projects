#state array will always be [position, velocity]
import numpy as np

def calculate_energy(state, potential_function, m):
    n = int(len(state)/2)

    position = state[:n]
    velocity = state[n:]
    #kinetic
    kinetic_energy = 0.5 * m * np.dot(velocity, velocity)
    #potential
    potential_energy = potential_function(position, m) #takes in position
    #lagrangian
    lagrangian = kinetic_energy - potential_energy
    #hamiltonian
    hamiltonian = kinetic_energy + potential_energy

    return kinetic_energy, potential_energy, lagrangian, hamiltonian


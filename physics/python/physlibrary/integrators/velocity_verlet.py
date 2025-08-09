def velocity_verlet_step(differential_equation, state, dt, t):
    n = int(len(state) / 2)

    acceleration = differential_equation(state, t)[n:]

    #where state[:n] are the positions and state[:n] are the velocities

    #new positions
    state[:n] = state[:n] + state[n:] * dt + 0.5 * acceleration * dt**2

    new_acceleration = differential_equation((state[:n], state[n:]), t + dt)[n:]

    #new velocities
    state[n:] = state[n:] + 0.5 * (acceleration + new_acceleration) * dt
    
    return state
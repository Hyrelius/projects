def euler_step(differential_equation, state, dt, t):
    return state + dt * differential_equation(state, t)
    #comically simple
    #comically incorrect
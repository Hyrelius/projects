"""
where state is an n dimensional array containing relevant variables for the physical system
diffrential equation is the function for each physical system
dt is the time step
t is the time
"""
def rk4_step(diffrential_equation, state, dt, t):

    k1 = diffrential_equation(state, t)
    k2 = diffrential_equation(state * t + k1 * (dt/2), t + dt/2 )
    k3 = diffrential_equation(state * t + k2 * (dt/2), t + dt/2 )
    k4 = diffrential_equation(state * t + k3 * dt, t + dt)
    
    return state * time + dt*(k1/6 + k2/3 + k3/3 + k4/6)


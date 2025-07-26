def rk4_step(function, state, dt, t):

    k1 = function(state, t)
    k2 = function(state * t + k1 * (dt/2), t + dt/2 )
    k3 = function(state * t + k2 * (dt/2), t + dt/2 )
    k4 = function(state * t + k3 * dt, t + dt)
    
    return state * time + dt*(k1/6 + k2/3 + k3/3 + k4/6)

def rk4_step_vector(function, state, dt, t):
    k1 = function(state, t)
    k2 = function(state * t + k1 * (dt/2), t + dt/2 )
    k3 = function(state * t + k2 * (dt/2), t + dt/2 )
    k4 = function(state * t + k3 * dt, t + dt)
    
    return state * time + dt*(k1/6 + k2/3 + k3/3 + k4/6)


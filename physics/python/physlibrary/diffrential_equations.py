import numpy as np
def basic(state, t):

    dxdt = state[2]
    dydt = state[3]
    dvxdt = 0
    dvydt = -9.81

    return np.array([dxdt, dydt, dvxdt, dvydt])
# task 1
# data from an array
# plot to verify
# calculate constants for each planet

import matplotlib.pyplot as plt
import numpy as np
# set array with data from "the internet"
planets = ["mercurary", "venus", "earth", "mars",
           "jupiter", "saturn", "uranus", "neptune"]
period = np.array([0.24109589, 0.61643836, 1, 1.88219178,
                   11.8712329, 29.4767123, 84.0739726, 164.90411])
orbital_semi_major_axis = np.array([0.38709893, 0.72333199, 1,
                                    1.52366231, 5.20288700, 9.53667594, 19.18916464, 30.06992276])

for i in range(len(orbital_semi_major_axis)):
    orbital_semi_major_axis[i] = orbital_semi_major_axis[i]**(3/2)

coefficients = np.polyfit(period, orbital_semi_major_axis, 1)
best_fit = np.poly1d(coefficients)

print(coefficients[0])

plt.scatter(orbital_semi_major_axis, period, color='blue', label=planets)
plt.plot(orbital_semi_major_axis, best_fit(orbital_semi_major_axis), "r-")
plt.xlabel('Orbital Semi Major Axis (AU)')
plt.ylabel('Orbital Period (years)')
plt.show()

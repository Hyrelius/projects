# task 1
# data from an array
# plot to verify
# calculate constants for each planet

import numpy as np
import matplotlib.pyplot as plt


planets = ["mercurary", "venus", "earth", "mars",
           "jupiter", "saturn", "uranus", "neptune"]
period = [0.24109589, 0.61643836, 1, 1.88219178,
          11.8712329, 29.4767123, 84.0739726, 164.90411]
orbital_semi_major_axis = [0.38709893, 0.72333199, 1,
                           1.52366231, 5.20288700, 9.53667594, 19.18916464, 30.06992276]
plt.figure(figsize=(10, 6))
plt.scatter(orbital_semi_major_axis, period, color='blue')
plt.xlabel('Orbital Semi Major Axis (AU)')
plt.ylabel('Orbital Period (years)')
plt.title('Orbital Period vs Semi Major Axis of Planets')
plt.xscale('log')
plt.yscale('log')
plt.grid(True, which="both", ls="--")
plt.show()

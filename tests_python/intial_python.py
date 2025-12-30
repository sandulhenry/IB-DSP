import os
import matplotlib.pyplot as plt
import sys
import csv
import numpy as np

print(f"Input file provided: {sys.argv[1]}")

y = []

with open(sys.argv[1], 'r') as file:
    r = csv.reader(file)
    for row in r:
        newrow = []
        for item in row:
            try:
                newrow.append(float(item))
            except:
                continue
        y.append(newrow)

for i in y:
    plt.plot(i)
    plt.show()


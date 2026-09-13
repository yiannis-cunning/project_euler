def sum_digits(val):
    ans = 0
    while(val != 0):
        ans += (val % 10)
        val -= (val % 10)
        val = val/10
    
    return ans



import matplotlib.pyplot as plt
import numpy as np



x = []
y = []

for i in range(10000):
    x.append(i)
    y.append(sum_digits(i))

plt.plot(x, y, label='Sine Wave') # Plots y vs x, adds a label for the legend

# Add labels, a title, and a legend
plt.xlabel('X-axis Label')
plt.ylabel('Y-axis Label')
plt.title('Simple Matplotlib Line Plot')

plt.grid(True) # Adds grid lines

# Display the plot
plt.show()
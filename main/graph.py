import matplotlib.pyplot as plt
import numpy as np

x_list = []
y_list = []

# read input.txt
with open('/home/harshitagupta/SPP/2020101078/saxpy-main/input.txt', 'r') as f:
    lines = f.readlines()
    for line in lines:
        n = float(line.split(' ')[0])
        matches = line.split(' ')[1]
        matches = float(matches.replace('\n', ''))
        x_list.append(n)
        y_list.append(matches)

# plot
# plt.ylim(10, 25)
plt.plot(x_list, y_list, 'g-')
plt.xlabel('Pattern Size')
plt.ylabel('Number of exact matches')
plt.title('Pattern Size Vs Exact Matches')
plt.show()
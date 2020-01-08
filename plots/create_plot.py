
import sys
import csv
import numpy as np
from matplotlib import pyplot as plt 

try:
    filename = sys.argv[1]
except IndexError:
    print('Wrong arguments!')
    sys.exit(1)

x = np.genfromtxt(filename, delimiter=',')

print(x[:,0])

plt.plot(x[:,0], x[:,1], label='weather')
plt.plot(x[:,0], x[:,2], label='generation')
plt.plot(x[:,0], x[:,3], label='consumption')
plt.plot(x[:,0], x[:,4], label='no_energy')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Energy generation and consumption')
plt.legend(loc='best')
plt.show()


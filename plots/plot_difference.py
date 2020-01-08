
import sys
import numpy as np
from matplotlib import pyplot as plt 

def num_to_weather(num):
    if num == 0:
        return 'sunny'
    elif num == 1:
        return 'middle'
    else:
        return 'cloudy'

try:
    filename = sys.argv[1]
except IndexError:
    print('Wrong arguments!')
    sys.exit(1)

csv = np.genfromtxt(filename, delimiter=',')

x = csv[:,0]
y1 = csv[:,2]
y2 = csv[:,3]

y = y1 - y2 

avg = np.sum(y) / y.size
print('average:', avg)
plt.axhline(y=avg, color="orange", linewidth=1)

plt.plot(x, y, label='difference')

my_xticks = [ num_to_weather(num) for num in csv[:,1] ]
print(my_xticks)
plt.xticks(x, my_xticks, rotation=60)

plt.axhline(y=0, color='black', linewidth=0.5)

plt.xlabel('days')
plt.ylabel('10^2 MJ of energy')
plt.title('Difference between energy generation and consumtion (1 month)')
plt.legend(loc='best')
plt.tight_layout()
plt.show()

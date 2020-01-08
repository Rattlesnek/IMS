
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
    filename_day = sys.argv[1]
    filename_res = sys.argv[2]
except IndexError:
    print('Wrong arguments!')
    sys.exit(1)

csv_day = np.genfromtxt(filename_day, delimiter=',')
csv_res = np.genfromtxt(filename_res, delimiter=',')

x = csv_res[:,0]
y = csv_res[:,1]

x_weather = csv_day[:,1]

plt.plot(x, y, label='reservoir_energy')

my_xticks = []
for num in x_weather:
    my_xticks.append(num_to_weather(num))
    my_xticks.append('.')

print(my_xticks)
plt.xticks(x, my_xticks, rotation=60)

plt.xlabel('days (weather + dot is single day)')
plt.ylabel('10^2 MJ of energy')
plt.title('Amount of energy stored in reservoir (1 month)')
plt.legend(loc='best')
plt.tight_layout()
plt.show()

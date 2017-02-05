import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys
from parse import compile 
SIZE = 100

buf = np.ndarray(shape=(6,SIZE),dtype=int)

fig, axarr = plt.subplots(6, sharex=True)
lines = []


def update(data):
    for i,l in enumerate(lines):
        l.set_ydata(data[i])
    return lines,


def data_gen():
    i = 0
    for line in sys.stdin:
        i = (i+1) % SIZE
        symbols = ['ax','ay','az','gx','gy','gz']
        next_set = parser.parse(line)
        if next_set is not None:
            for i,b in enumerate(buf):
                buf[i] = next_set[symbols[i]]
                print(next_set[symbols[i]],symbols[i])
            yield buf

for i,a  in enumerate(axarr):
    l, = axarr[i].plot(buf[i])
    lines.append(l)
    axarr[i].set_ylim(-20000,20000)

parser = compile("  {ax:d} \t {ay:d} \t {az:d} \t {gx:d} \t {gy:d} \t {gz:d}\n");
ani = animation.FuncAnimation(fig, update, data_gen, interval=1)
plt.show()



#for line in sys.stdin:
#    parser = compile("  {ax:d} \t {ay:d} \t {az:d} \t {gx:d} \t {gy:d} \t {gz:d}\n");
#    next_set = parser.parse(line)
#    if next_set is not None:
#        print (next_set["ay"])

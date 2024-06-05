import random

f = open("Trace.txt", "r")
g = open("testcase.txt", "w")

mem = dict()


for line in f.readlines():
    line = line.strip("\n")
    address = int(line, base=16)
    address = int(round(address/4))*4
    print(address)
    if address not in mem:
        value = random.randrange(0, pow(2, 32))
        mem[address] = value
        g.writelines(f"w {hex(address)[2:]} {hex(value)[2:]}\n")
    else:
        action = random.randrange(0, 4)
        if action < 1:
            value = random.randrange(0, pow(2, 32))
            mem[address] = value            
            g.writelines(f"w {hex(address)[2:]} {hex(value)[2:]}\n")
        else:
            g.writelines(f"r {hex(address)[2:]}\n")
    
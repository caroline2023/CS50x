import csv
from sys import argv, exit

if len(argv) != 3:  # check the number of command-line arguments
    print("bruh")
    exit(1)

file = open(argv[1], "r")  # open the things
datareader = csv.reader(file)
data = []  # so now its a 2d array
for x in datareader:
    data.append(x)

f = open(argv[2], "r")  # open the sequence
sequence = f.read()

columns = len(data[0])
rows = len(data)

thing = {}
for i in range(1, columns):
    thing[data[0][i]] = 0


for seq in thing:
    n = len(seq)
    now = False
    i = 0
    max = 0  # keep track of max amount of occurences so far
    x = 0
    while True:
        if i > len(sequence) - n:  # we've reached the end 
            break
        
        if sequence[i:i + n] == seq:
            now = True
        else: 
            now = False
            
        if now == False:
            x = 0
            i += 1
        else:
            i += n
            x += 1
            if x > max:
                max = x
    thing[seq] = max  # set that dict value
 
for i in range(1, rows):
    match = True  # i think we need this?
    for j in range(1, columns):
        if int(data[i][j]) != thing[data[0][j]]:
            match = False
            break
    if match == True:
        print(f"{data[i][0]}")
        exit(0)

print("No match")
    
while True:
    try:
        h = int(input("Height: ")) 
    except ValueError: 
        continue
    if 0 < h < 9:
        break

for i in range(h):
    for j in range(h - 1 - i):  # to align
        print(" ", end="")
    
    for k in range(i + 1):  # first set of hashes
        print("#", end="")
    print("  ", end="")  # blank space baby
    
    for l in range(i + 1):
        print("#", end="")  # remaining hashes
    print()
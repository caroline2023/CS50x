import re

while True:
    num = input("Number: ")
    x = len(num)
    try: 
        a = int(num)
    except ValueError:  # reject ones that dont work
        continue
    break
    

def main():
    if checksum(num):
        if re.search("^4", num):
            if x == 13 or x == 16:  # is it visa
                print("VISA")
            else:
                print("INVALID")
        elif re.search("^3[47]", num):  # is it amex
            if x == 15:
                print("AMEX")
            else:
                print("INVALID")
        elif re.search("^5[1-5]", num):  # is it mastercard
            if x == 16:
                print("MASTERCARD")
            else:
                print("INVALID")
        else: 
            print("INVALID")  # other case
    else: 
        print("INVALID")


def checksum(num):
    y = 0  # yeah that
    
    for i in range(x - 2, -1, -2):  # the two digit things
        z = 2 * int(num[i])
        y += (z // 10 + z % 10) 
    
    for j in range(x - 1, -1, -2):
        y += int(num[j])
    
    if y % 10 == 0:  # is it valid
        return True
    else:
        return False


main()

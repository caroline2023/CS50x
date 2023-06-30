from cs50 import SQL
import csv
from sys import argv, exit

if len(argv) != 2:  # check the number of command-line arguments
    print("bruh")
    exit(1)

house = argv[1]  # make things easier

db = SQL("sqlite:///students.db")
ppl = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", 
                 house)  # should return a list of dicts

for i in range(len(ppl)):
    first = ppl[i]["first"]
    middle = ppl[i]["middle"]
    last = ppl[i]["last"]
    birth = ppl[i]["birth"]
    if middle != None:
        print(f"{first} {middle} {last}, born {birth}")  # i think we should consider the cases here
    else:
        print(f"{first} {last}, born {birth}")

from cs50 import SQL
import csv
from sys import argv, exit

if len(argv) != 2:  # check the number of command-line arguments
    print("bruh")
    exit(1)

db = SQL("sqlite:///students.db")

# open file thing
with open(argv[1], "r") as ppl:
    
    # create DictReader
    reader = csv.DictReader(ppl)
    
    for row in reader:
        name = row["name"]
        full = name.split()  # take care of first middle last
        if len(full) == 2:
            first = full[0]
            middle = None
            last = full[1]
        elif len(full) == 3:  # elif in case theres more idk
            first = full[0]
            middle = full[1]
            last = full[2]
        
        house = row["house"]
        birth = row["birth"]
        
        # put it into the thing
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   first, middle, last, house, birth)

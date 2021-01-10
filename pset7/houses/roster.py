from sys import argv, exit
from cs50 import SQL

# Check number of command line arguments
if len(argv) != 2:
    print("Incorrect number of command-line arguments. Must only include a single house name after roster.py")
    exit(1)

# Open students.db
db = SQL("sqlite:///students.db")

# Query data from students.db
students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

# Print students of the inputted house
for student in students:
    first = student["first"]
    middle = student["middle"]
    last = student["last"]
    birth = student["birth"]

    if student["middle"] == None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")
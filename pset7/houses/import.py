from sys import argv, exit
import csv
from cs50 import SQL

# Check number of command line arguments
if len(argv) != 2:
    print("Incorrect number of command-line arguments. Must only include a single csv file after import.py")
    exit(1)

db = SQL("sqlite:///students.db")

# Open csv file and start writing into DB
with open(argv[1]) as studentslist:

    # Create DictReader
    reader = csv.DictReader(studentslist)

    # Iterate over csv file
    for row in reader:

        # Split name into first, middle and last then insert data into students.db
        fullname = row["name"].split()

        # Check if full name contains 3 or 2 words
        if len(fullname) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       fullname[0], fullname[1], fullname[2], row["house"], row["birth"])
        else:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)",
                       fullname[0], fullname[1], row["house"], row["birth"])
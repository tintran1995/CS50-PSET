from sys import argv, exit
import csv

if len(argv) != 3:
    print("Must enter two command line argumes")
    exit(1)

database = []

# Open and import csv data into list
with open(argv[1], newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        database.append(row)

# Open and import txt data into a variable
with open(argv[2], "r") as txtfile:
    sequence = txtfile.read()

# Get column headings from csv
STR = []
for key in database[0]:
    STR.append(key)

# Predefine STR counts
STRcount = [0] * (len(STR) - 1)

# Find the max consecutive STR counts
for i in range(0, len(STR) - 1, 1):
    sequencecount = [0] * len(sequence)
    STRlen = len(STR[i + 1])

    for j in range(len(sequence)):
        if sequence[j:(j + STRlen)] == STR[i + 1]:
            for k in range(j, len(sequence), STRlen):
                if sequence[k:(k + STRlen)] == STR[i + 1]:
                    sequencecount[j] += 1
                else:
                    break

    STRcount[i] = max(sequencecount)


# Compare STR counts against databases
for i in range(len(database)):
    match = 0

    for j in range(len(STRcount)):
        if STRcount[j] == int(database[i][STR[j + 1]]):
            match += 1

    if match == len(STRcount):
        name = database[i]['name']
        break
    else:
        name = "No match"

# Print out name if matched
print(name)

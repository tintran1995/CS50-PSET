from cs50 import get_int

# prompt the user for height until a value between 1-8 inclusive is entered
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for i in range(height):
    print(" " * (height - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))
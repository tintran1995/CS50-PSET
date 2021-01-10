from cs50 import get_int

# Prompt user for card number
card = get_int("Number: ")

# Assign digits to array
digits = [int(x) for x in str(card)]

# Calculate sum
sum = 0

for i in range(len(digits) - 2, -1 or -2, -2):
    if (digits[i] * 2) > 0:
        sum = sum + (int(digits[i] * 2 / 10)) % 10 + (digits[i] * 2) % 10
    else:
        sum = sum + (digits[i] * 2) % 10

for i in range(len(digits) - 1, -1 or -2, -2):
    sum = sum + digits[i]

# Check for card type
if (sum % 10) == 0:
    if len(digits) == 15 and digits[0] == 3 and (digits[1] == 4 or digits[1] == 7):
        print("AMEX")
    elif len(digits) == 16 and digits[0] == 5 and (digits[1] in [1, 2, 3, 4, 5]):
        print("MASTERCARD")
    elif (len(digits) == 13 or len(digits) == 16) and digits[0] == 4:
        print("VISA")
else:
    print("INVALID")
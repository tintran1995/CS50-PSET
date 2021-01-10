from cs50 import get_string

# Get text from user
text = get_string("Text: ")
# Calculate number of letters, words and sentences
letters = 0
words = 1
sentences = 0

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1

    if i < (len(text) - 1):
        if text[i] == " " and (text[i + 1] != " "):
            words += 1

    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

# Calculate the index
index = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {int(round(index))}")
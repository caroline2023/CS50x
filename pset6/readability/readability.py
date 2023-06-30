import re

text = input("Text: ")

w = 1 + len(re.findall(" ", text))  # number of words in text
l = len(re.findall("[a-zA-Z]", text))  # number of letters in text
s = len(re.findall("[.?!]", text))  # number of sentences in text

L = l / w * 100
S = s / w * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

if 0 < index < 16:
    print(f"Grade {index}")
elif index < 1:
    print("Before Grade 1")
else: 
    print("Grade 16+")
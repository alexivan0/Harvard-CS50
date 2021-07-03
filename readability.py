from cs50 import get_string

input = get_string("Text: ")

L = 0
W = 0
S = 0

for i in range(len(input)):
    if input[i].isalpha() == True:
        L += 1
    if input[i] == " " or i + 1 == len(input):
        W += 1
    if input[i] == "." or input[i] == "?" or input[i] == "!":
        S += 1

avgL = L / W * 100
avgS = S / W * 100

index = round(0.0588 * avgL - 0.296 * avgS - 15.8)

if index < 16:
    print(f"Grade: {index}")
elif index >= 16:
    print("Grade 16+")
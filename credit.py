from cs50 import get_int
from cs50 import get_string

number = get_int("Number: ")
strnumber = str(number)
checksum = 0
muliply = 0
reversenumber = strnumber[::-1]
for i in range(1,len(reversenumber),2):
    multiply = int(reversenumber[i]) * 2
    if len(str(multiply)) == 2:
        checksum = checksum + int(str(multiply)[0]) + int(str(multiply)[1])
    else:
        checksum = checksum + multiply
for i in range(0,len(reversenumber),2):
    checksum = checksum + int(reversenumber[i])



if checksum % 10 == 0 and len(strnumber) == 15 and ((strnumber)[0:2] == str(34) or (strnumber)[0:2] == str(37)):
    print("AMEX")
elif checksum % 10 == 0 and len(strnumber) == 16 and (50 < int((strnumber)[0:2]) < 56):
    print("MASTERCARD")
elif checksum % 10 == 0 and (len(strnumber) == 13 or len(strnumber) == 16) and (strnumber)[0] == str(4):
    print("VISA")
else:
    print("INVALID")
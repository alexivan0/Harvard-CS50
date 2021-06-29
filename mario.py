import cs50

while True:
    size = cs50.get_int("Height: ")
    if(size > 0 and size < 9):
        break

for x in range(size + 1):
    print(" " * (size - x), end="")
    print("#" * x, end="")
    print("  ", end="")
    print("#" * x, end="")
    print(" " * (size - x))
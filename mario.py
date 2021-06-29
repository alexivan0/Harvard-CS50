from cs50 import get_int

while True:
    size = get_int("Height: ")
    if size > 0 and size < 9:
        break

for x in range(1, size + 1):
    print(" " * (size - x), end="")
    print("#" * x, end="")
    print("  ", end="")
    print("#" * x, end="")
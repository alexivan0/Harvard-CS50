size = int(input("Height: "))
for x in range(size + 1):
    print(" " * (size - x), end="")
    print("#" * x, end="")
    print("  ", end="")
    print("#" * x, end="")
    print(" " * (size - x))
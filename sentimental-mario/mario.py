while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height < 9:
            break
    except ValueError:
        pass

for i in range(1, height + 1):
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print(" " * 2, end="")
    print("#" * i)

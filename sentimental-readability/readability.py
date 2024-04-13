def main():
    text = input("Text: ")
    index = coleman_liau(text)
    print_grade(index)


def print_grade(index):
    grade = round(index)
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def coleman_liau(text):
    l = 0
    w = 0
    s = 0

    words = text.split()
    for word in words:
        w += 1
        for char in word:
            if char.isalnum():
                l += 1
            elif char in [".", "!", "?"]:
                s += 1

    L = (l / w) * 100
    S = (s / w) * 100

    index = 0.0588 * L - 0.296 * S - 15.8
    return index


main()

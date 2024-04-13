def main():
    while True:
        try:
            card_n = input("Number: ").strip()
            int(card_n)
            break
        except ValueError:
            pass

    is_valid = checksum(card_n)

    if is_valid:
        brand = get_brand(card_n)
    else:
        print("INVALID")
        return 1
    print(brand)


def checksum(card_n):
    reversed_n = card_n[::-1]
    sum = 0

    for i, digit in enumerate(reversed_n):
        digit = int(digit)

        if i % 2 != 0:
            product = digit * 2

            if len(str(product)) == 2:
                for d in str(product):
                    sum += int(d)
            else:
                sum += product
        else:
            sum += digit

    return sum % 10 == 0


def get_brand(card_n):
    if card_n[0] == "4" and len(card_n) == 16 or len(card_n) == 13:
        return "VISA"
    elif card_n[0:2] == "34" or card_n[0:2] == "37" and len(card_n) == 15:
        return "AMEX"
    elif card_n[0] == "5" and int(card_n[1]) in range(1, 6) and len(card_n) == 16:
        return "MASTERCARD"
    else:
        return "INVALID"


main()

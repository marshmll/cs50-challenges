#include <cs50.h>
#include <stdio.h>

bool checksum(long cardNumber);
string get_brand(long cardNumber);
int get_length(long cardNumber);
long ten_to_power(int power);

const int MAX_CARD_LENGTH = 16;

int main(void)
{
    long card_number = get_long("Number: ");
    int card_length = get_length(card_number);
    bool is_valid = checksum(card_number);

    if (!is_valid)
    {
        printf("INVALID\n");
        return 0;
    }

    string brand = get_brand(card_number);
    printf("%s\n", brand);
}

bool checksum(long card_number)
{
    int final_sum = 0;

    // Luhn's Algorithm
    // The Luhn's Algorithm verify if a card number is formatted
    // in a valid way.
    for (int i = 1; i <= MAX_CARD_LENGTH; i++)
    {
        long module = card_number % ten_to_power(i);
        int digit = module / ten_to_power(i - 1);
        // Executes only to number’s second-to-last digit.
        if (i % 2 == 0)
        {
            int digit_product = digit * 2;
            // If the digit product has two digits (including numbers ending with 0), split and add them.
            if (digit_product % 10 >= 0)
            {
                int first_module = digit_product % ten_to_power(1);
                int second_module = digit_product % ten_to_power(2);
                // Transforms the modules to actual digits.
                int first_digit = first_module / ten_to_power(0);
                int second_digit = second_module / ten_to_power(1);

                int inner_sum = first_digit + second_digit;

                final_sum += inner_sum;
            }
            // Else just add the product to the final sum.
            else
            {
                final_sum += digit_product;
            }
        }
        // Executes to all remaining numbers.
        else
        {
            final_sum += digit;
        }
    }
    // If the final sum ends with digit 0, then it's a valid card number format.
    printf("%i\n", final_sum);
    if (final_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string get_brand(long card_number)
{
    int card_length = get_length(card_number);

    if (card_length > MAX_CARD_LENGTH)
    {
        return "INVALID";
    }
    // Declares variables that will store digits to verification
    int thirteenth_digit;
    int fourteenth_digit;
    int fifteenth_digit;
    int sixteenth_digit;

    for (int i = 1; i <= MAX_CARD_LENGTH; i++)
    {
        long module = card_number % ten_to_power(i);
        int digit = module / ten_to_power(i - 1);
        // These conditionals collect some important digits from the card.
        if (i == 13)
        {
            thirteenth_digit = digit;
        }

        if (i == 14)
        {
            fourteenth_digit = digit;
        }

        if (i == 15)
        {
            fifteenth_digit = digit;
        }

        if (i == 16)
        {
            sixteenth_digit = digit;
        }
    }
    // These conditionals search for card number patterns and return the respective brand.
    if (card_length == 13 && thirteenth_digit == 4) // VISA (13 digits and start with 4)
    {
        return "VISA";
    }

    else if (card_length == 15 && fifteenth_digit == 3) // AMEX (15 digits and start with 34 or 37)
    {
        if (fourteenth_digit == 4 || fourteenth_digit == 7)
        {
            return "AMEX";
        }
    }

    else if (card_length == 16 && sixteenth_digit == 4) // VISA (16 digits and starts with 4)
    {
        return "VISA";
    }

    else if (card_length == 16 && sixteenth_digit == 5) // MASTERCARD (16 digits and starts with 51, 52, 53, 54 or 55)
    {
        for (int i = 1; i <= 5; i++)
        {
            if (fifteenth_digit == i)
            {
                return "MASTERCARD";
                break;
            }
        }
    }
    // If none of the previous brands are true, the program returns INVALID.
    return "INVALID";
}

int get_length(long number)
{
    int counter = 0;
    long n = number;

    while (n != 0)
    {
        n = n / 10;
        counter++;
    }

    return counter;
}

// *Only calculates powers starting from 0.
long ten_to_power(int power)
{
    long result = 1;

    if (power == 0)
    {
        return result;
    }

    for (int i = 0; i < power; i++)
    {
        result = result * 10;
    }

    return result;
}

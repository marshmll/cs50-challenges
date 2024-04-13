#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void print_ciphertext(string plaintext, string key);
bool has_only_alpha(string key);
bool has_repeated_chars(string key);

const int KEY_LENGTH = 26;

int main(int argc, string argv[])
{
    string key = "";

    if (argc < 2)
    {
        printf("ERROR: Expected 1 argument 'key'. Received %i.\n", argc - 1);
        return 1;
    }
    else if (argc > 2)
    {
        printf("ERROR: Expected 1 argument 'key'. Received %i.\n", argc - 1);
        return 1;
    }
    else
    {
        key = argv[1];
    }

    int key_length = strlen(key);

    if (key_length != KEY_LENGTH)
    {
        printf("ERROR: Invalid key length. Expected: %i, received: %i\n", KEY_LENGTH, key_length);
        return 1;
    }

    if (!has_only_alpha(key))
    {
        printf("ERROR: Key must have only alphabetical characters.\n");
        return 1;
    }

    if (has_repeated_chars(key))
    {
        printf("ERROR: Key must not repeat any alphabetical character.\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    print_ciphertext(plaintext, key);
}

void print_ciphertext(string plaintext, string key)
{
    int plaintext_length = strlen(plaintext);
    char ciphertext[plaintext_length];

    printf("ciphertext: ");
    for (int i = 0; i < plaintext_length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = key[plaintext[i] - 'A'];
                printf("%c", toupper(ciphertext[i]));
            }
            else if (islower(plaintext[i]))
            {
                ciphertext[i] = key[plaintext[i] - 'a'];
                printf("%c", tolower(ciphertext[i]));
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

bool has_only_alpha(string key)
{
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
            break;
        }
    }
    return true;
}

bool has_repeated_chars(string key)
{
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        for (int j = 0; j < KEY_LENGTH; j++)
        {
            if (key[i] == key[j] && i != j)
            {
                return true;
            }
        }
    }
    return false;
}

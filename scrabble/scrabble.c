#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_score(string word);
void print_winner(int score1, int score2);

const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Prompt the user for two words.
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Calculates word scores.
    int score1 = calculate_score(word1);
    int score2 = calculate_score(word2);

    // Prints the winner.
    print_winner(score1, score2);
}

int calculate_score(string word)
{
    int score = 0;
    int word_length = strlen(word);

    // iterate for all chars in the string
    for (int i = 0; i < word_length; i++)
    {
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A']; // If the char is uppercase, subtract from
                                            // its value the value of 'A' and get index to POINTS.
        }
        else if (islower(word[i])) // If the char is lowecase, subtract from
                                   // its value the value of 'a' and get index to POINTS.
        {
            score += POINTS[word[i] - 'a'];
        }
        // If its not a letter, it'll pass through.
    }
    return score;
}

// Compares both scores and check for winner/tie.
void print_winner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

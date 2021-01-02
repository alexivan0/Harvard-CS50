#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) // argc = number of arguments, argv[] the position of the arguments themselves.
{
    int key;
    if (argc != 2)  // Check if the number of arguments is 2.
    {
        printf("Usage: ./caesar key\n");
        return 1; // Stop the whole program.
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++) // Go through the whole string.
    {
        if (isdigit(argv[1][i])) //Check if the number is a digit.
        {
            continue;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 2;
        }
    }
    key = atoi(argv[1]);
    string plaintext = get_string("Text:\n");
    string ciphertext = malloc(strlen(plaintext)); //Alocate (strlen(plaintext) memory to the ciphertext string.
    string alphaindex = malloc(strlen(plaintext)); //Alocate (strlen(plaintext) memory to the alphaindex string.
    for (int i = 0, n = strlen(plaintext); i < n; i++) // Go through the whole string.
    {
        if (isupper(plaintext[i])) //Check if it's a uppercase letter.
        {
            alphaindex[i] = plaintext[i] - 65; // Convert to alphabetical index in order to aply the formula down below.
            ciphertext[i] = (alphaindex[i] + key) % 26; // Formula that cycles the alphabet when reaching the end, instead of going further.
            ciphertext[i] = ciphertext[i] + 65; // Convert from alphabetical index to ASCII in order to represent real letters.
        }
        else if (islower(plaintext[i]))  //Check if it's a lowercase letter.
        {
            alphaindex[i] = plaintext[i] - 97;
            ciphertext[i] = (alphaindex[i] + key) % 26;
            ciphertext[i] = ciphertext[i] + 97;

        }
        else
        {
            ciphertext[i] = ciphertext[i] + plaintext[i]; //If it's not a letter, then keep it as it is.
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    free(ciphertext); // Release the allocated memory to prevent memory leaks.
    free(alphaindex); // Release the allocated memory to prevent memory leaks.
}

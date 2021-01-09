#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc != 2) // Checks for invalid key
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    int n = strlen(argv[1]);
    for (int i = 0; i < n; i++) // Checks for invalid key
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Usage: ./substitution key");
            return 1;
        }
    }

    if (strlen(argv[1]) != 26) // Checks for invalid key
    {
        printf("Key must contain 26 characters.");
        return 1;
    }
    for (int i = 0; i < n ; i++) // Checks for invalid key
    {
        for (int j = i + 1; j < n; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    string plaintext = get_string("plaintext:");
    string ciphertext = malloc(strlen(plaintext));  // Alocate memory

    for (int i = 0; i < strlen(plaintext); i++) // Go through all the alphabet characters
    {
        for (int j = 0, z = strlen(key); j < z; j++) // Go through all the plaintext characters
        {
            if (plaintext[i] == 65 + j) // Check if the character is the same as the alphabet character
            {
                ciphertext[i] = toupper(key[j]); // Encrypt the plaintext to the encription key character,
            }                                    // using the same slot as the alphabet character.

            else if (plaintext[i] == 97 + j) //For upp
            {
                ciphertext[i] = tolower(key[j]);
            }
            else if (isalpha(plaintext[i]) == 0)
            {
                ciphertext[i] = plaintext[i];
            }
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    free(ciphertext); // Return the allocated memory
    return 0;
}


#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

    string s = get_string("Text: \n");  //Prompt the user for input
    int letters = 0;
    int spaces = 0;
    int words = 0;
    int sentences = 0;
    int i;
    float L;
    float S;
    int index;
    for (i = 0; s[i] != '\0'; i++) // Advance through the string one character at a time.
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) // If the string character is a letter then add it to "spaces".
        {

            letters++;
        }
        else if (s[i] == ' ') // 32 = Space in ASCII. If the string character is a space, then add 1 to "spaces".
        {
            spaces++;
        }
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?') // If the string character is . or ! or ?, then add 1 to "sentences".
        {
            sentences++;
        }
    }
    words = spaces + 1;
    L = (float)letters / (float)words * 100;
    S = (float)sentences / (float)words * 100;
    index = (round)(0.0588 * L - 0.296 * S - 15.8);

    if (index > 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
}

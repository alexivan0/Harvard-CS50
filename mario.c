#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Width[1-100]: ");
    }
    while (n < 1 || n > 100);

    for (int i = 0; i < n; i++)  //Printing each row n times
    {
        for (int a = n - 1; a > i; a--) // Printing spaces each row
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)  //Printing hashes each row
        {
            printf("#");

        }

        printf("  ");  //Printing double spaces each row

        for (int k = 0; k <= i; k++)  //Printing hashes each row
        {
            printf("#");
        }

        printf("\n");
    }

}
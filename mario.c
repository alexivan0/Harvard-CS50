#include <cs50.h>
#include <stdio.h>

int main(void){

    int n;
    do
    {
    n = get_int("Width[1-8]: ");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        for (int a = 7; a > i; a--)
        {
        printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");

        }
        printf("\n");
    }

}
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    do
    {
        float dollars = get_float("Change owed?(Dollars): ");  // Ask for change owed
    }
    while (dollars < 0);

    int cents = round(dollars * 100);

    int rmncents = cents;

    int pennies = 0;

    while (rmncents >= 25)
    {

        rmncents = rmncents - 25;
        pennies++;
    }
    while (rmncents >= 10 && rmncents < 25)
    {

        rmncents = rmncents - 10;
        pennies++;
    }
    while (rmncents >= 5 && rmncents < 10)
    {

        rmncents = rmncents - 5;
        pennies++;
    }
    while (rmncents >= 1 && rmncents < 5)
    {

        rmncents = rmncents - 1;
        pennies++;
    }
    if (rmncents < 1)
    {
        printf("%i\n", pennies);
    }


}
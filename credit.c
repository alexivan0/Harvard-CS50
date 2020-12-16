#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long cardnum = get_long("Enter your card number: "); // Ask for card number
    int count;
    int last2digits;
    int lastdigit;
    int checksum = 0; // initialize checksum and store the value 0 in checksum;
    long i;
    long j;
    long cardcounter;
    long cardnum2num;
    cardnum2num = cardnum; // store the cardnum value in the cardnum2num variable
    cardnum = cardnum / 10; // remove the last digit from cardnum
    cardcounter = cardnum; // store the cardnum value in the cardcounter variable


    for (count = 3 ; cardcounter >= 100 ; count++) //Count how many digits it has
    {
        cardcounter = cardcounter / 10; // remove the last digit
        last2digits = cardcounter % 100; // store the last 2 digits
    }
    for (i = cardnum ; i > 0 ; i = i / 100) // Multiply every other digit by 2
    {
        lastdigit = i % 10; // store the last digit
        if (lastdigit * 2 >= 10) // check if the last digit*2 is greater than 10
        {
            lastdigit = (lastdigit * 2) % 10 + (lastdigit * 2) / 10; // if the multiplied digit is bigger than 10 then add the product's digits
            checksum = checksum + lastdigit; // add the last operation to the checksum
        }
        else
        {
            checksum = checksum + lastdigit * 2; // add the lastdigit*2 to the checksum
        }
    }
    for (j = cardnum2num ; j > 0 ; j = j / 100) // remove the last 2 digits
    {
        lastdigit = j % 10; // store the last digit
        checksum = checksum + lastdigit; // add the last digit to the checksum
    }
    if ((count == 16 || count == 13) && checksum % 10 == 0
        && (last2digits >= 40 && last2digits < 50)) //check if confirms the VISA conditions
    {
        printf("%s\n", "VISA\n");
    }
    else if (count == 16 && checksum % 10 == 0
             && (last2digits >= 51 && last2digits <= 55)) //check if it confirms the MASTERCARD conditions
    {
        printf("%s\n", "MASTERCARD\n");
    }
    else if (count == 15 && checksum % 10 == 0
             && (last2digits == 34 || last2digits == 37)) // check if it confirms the AMEX conditions
    {
        printf("%s\n", "AMEX\n");
    }
    else // Otherwise it's invalid
    {
        printf("%s\n", "INVALID\n");
    }

}
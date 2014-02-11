#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{   
    float n;
    int x;
    
    // Ask for user input.
    do
    {
        printf("Hello. How much change is owed?\n");
        n = GetFloat();
        x = round(n * 100);
    }
    while (n < 0);
    
    int numberofcoins = 0;
    int remainder = x;
    
    // Checks if quarters can be used, and returns remainder.
    numberofcoins = x / 25;
    remainder = x % 25;    
    
    // Checks if dimes can be used, and returns remainder.
    numberofcoins = numberofcoins + (remainder / 10);
    remainder = remainder % 10;
    
    // Checks if nickels can be used, and returns remainder.
    numberofcoins = numberofcoins + (remainder / 5);
    remainder = remainder % 5;
    
    // Adds remainder under 5 cents to total number of coins.
    numberofcoins = numberofcoins + remainder;  
    
    // Prints total change owed.
    printf("You owe %d coins for change.\n", numberofcoins);
}

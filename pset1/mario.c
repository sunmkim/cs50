#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    
    // Gets input from user
    do
    { 
        printf("Height: ");
        n = GetInt();
    }
    while (n > 23 || n < 0);
    
    //Prints hashes    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (j < (n-(i+1)))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

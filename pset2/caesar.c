#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{   
    // Checks for correct usage of argc
    if (argc != 2)
    {
        printf("Invalid command line argument. Please try again.\n");
        return 1;
    }
    
    // Converts argv[] string into int
    int key = atoi(argv[1]) % 26;
    
    // Obtains user input
    string ptxt = GetString();
    
    // Encrypts plaintext into cyphertext
    for (int i = 0, n = strlen(ptxt); i < n; i++)
    {   
        if (isalpha(ptxt[i]))
        {   
            char letter = ptxt[i];
            int asciinum = letter;
            
            // Encrypt upper-case
            if (asciinum > 64 && asciinum + key < 91)
            {   
                int ctxt = asciinum + key;
                char cletter = ctxt;
                printf("%c", cletter);
            }
            else if (asciinum + key > 90 && isupper(ptxt[i]))
            {
                int ctxt = (asciinum + key) - 90 + 64;
                char cletter = ctxt;
                printf("%c", cletter);
            }
            
            // Encrypt lower-case
            if (asciinum > 96 && asciinum + key < 123)
            {
                int ctxt = asciinum + key; 
                char cletter = ctxt;
                printf("%c", cletter);
            }
            else if (asciinum + key > 122 && islower(ptxt[i]))
            {
                int ctxt = (asciinum + key) - 122 + 96;
                char cletter = ctxt;
                printf("%c", cletter);
            }
        }
        
        // Prints non-letters as they are.
        else
        {    
            printf("%c", ptxt[i]);
        }
    }
    
    printf("\n");
    
}

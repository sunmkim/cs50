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
    
    string key = argv[1];
    int keylen = strlen(argv[1]);
    
    // Obtains user input
    string ptxt = GetString();
    
    int count = 0;
    
    // Encrypts plaintext into cyphertext
    for (int i = 0; i < strlen(ptxt); i++)
    {   
        int key_asciinum;
        
        if (isalpha(ptxt[i]))
        {   
            int lowerascii = tolower(key[count % keylen]); // converts keyword to all lower
            key_asciinum = lowerascii - 97; // finds alphebetical index of each letter in key
            
            count++;
            
            int asciinum = ptxt[i];
            
            // Encrypt upper-case
            if (asciinum > 64 && asciinum + key_asciinum < 91)
            {   
                int ctxt = asciinum + key_asciinum;
                char cletter = ctxt;
                printf("%c", cletter);
            }
            else if (asciinum + key_asciinum > 90 && isupper(ptxt[i]))
            {
                int ctxt = (asciinum + key_asciinum) - 90 + 64;
                char cletter = ctxt;
                printf("%c", cletter);
            }
            
            // Encrypt lower-case
            if (asciinum > 96 && asciinum + key_asciinum < 123)
            {
                int ctxt = asciinum + key_asciinum; 
                char cletter = ctxt;
                printf("%c", cletter);
            }
            else if (asciinum + key_asciinum > 122 && islower(ptxt[i]))
            {
                int ctxt = (asciinum + key_asciinum) - 122 + 96;
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
